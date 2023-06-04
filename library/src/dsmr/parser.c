//
// Created by guust on 5/28/23.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dsmr/parser.h"
#include "dsmr/tokenizer.h"
#include "dsmr/types.h"


void dump_telegram(t_telegram *telegram) {
    printf("Model specification: %c%c%c\n",
           telegram->model_specification[0],
           telegram->model_specification[1],
           telegram->model_specification[2]);
    printf("Model identification: ");
    for (int i = 0; i < SPECIFICATION_CAPACITY; ++i) {
        if (telegram->identification[i] == '\0') {
            break;
        }
        printf("%c", telegram->identification[i]);
    }
    printf("\n");
    printf("Checksum: %c%c%c%c\n",
           telegram->checksum[0],
           telegram->checksum[1],
           telegram->checksum[2],
           telegram->checksum[3]);

    printf("Amount of data entries: %d \n", telegram->amount_of_data_entries);
}

t_telegram init_telegram() {
    t_telegram telegram = {
            .model_specification={'\0'},
            .identification ={'\0'},
            .amount_of_data_entries =0,
            .checksum={'\0'},
            .fully_parsed =0,
    };
    for (int i = 0; i < DSMR_DATA_CAPACITY; ++i) {
        t_telegram_data data = {
                .initialized = 0,
                .type = {'\0'},
                .channel = {'\0'}
        };
        telegram.data[i] = data;
    }
    return telegram;
}


static void _read_model_specification(Tokenizer *tokenizer, t_telegram *telegram) {
    telegram->model_specification[0] = tokenizer_next_char(tokenizer);
    telegram->model_specification[1] = tokenizer_next_char(tokenizer);
    telegram->model_specification[2] = tokenizer_next_char(tokenizer);

}

static int _read_model_identification(Tokenizer *tokenizer, t_telegram *telegram) {
    size_t ctr = 0;
    while (tokenizer_has_next(tokenizer)) {
        if (ctr + 1 >= SPECIFICATION_CAPACITY) {
            //TODO error
            return 0;
        }
        char token = tokenizer_next_char(tokenizer);
        if (token == DSMR_TKNZR_CR) {
            break;
        }
        telegram->identification[ctr++] = token;
    }
    //move idx one back so we dont parser \r
    tokenizer->current_idx--;
    return 1;
}

static int _verify_end_of_header(Tokenizer *tokenizer) {
    if (tokenizer_next_char(tokenizer) != DSMR_TKNZR_CR) {
        return 0;
    }
    if (tokenizer_next_char(tokenizer) != DSMR_TKNZR_LF) {
        return 0;
    }
    if (tokenizer_next_char(tokenizer) != DSMR_TKNZR_CR) {
        return 0;
    }
    if (tokenizer_next_char(tokenizer) != DSMR_TKNZR_LF) {
        return 0;
    }
    return 1;
}


static int _verify_end_of_telegram(Tokenizer *tokenizer) {
    if (tokenizer_next_char(tokenizer) != DSMR_TKNZR_CR) {
        return 0;
    }
    if (tokenizer_next_char(tokenizer) != DSMR_TKNZR_LF) {
        return 0;
    }
    return 1;
}

int _parse_measurements(Tokenizer *pTokenizer, t_telegram *pTelegram) {
    while (tokenizer_has_next(pTokenizer)) {
        char token = tokenizer_next_char(pTokenizer);
        if (token == DSMR_TKNZR_END_DATA) {
            break;
        }
        t_telegram_data telegram_data;
        //OBIS channel
        int idx_channel = 0;
        while (tokenizer_has_next(pTokenizer)) {
            token = tokenizer_next_char(pTokenizer);
            if (token == ':') {
                break;
            }
            telegram_data.channel[idx_channel++] = token;
        }
        int idx_type = 0;
        while (tokenizer_has_next(pTokenizer)) {
            token = tokenizer_next_char(pTokenizer);
            if (token == '(') {
                pTokenizer->current_idx--;
                break;
            }
            telegram_data.type[idx_type++] = token;
        }


        if (token == DSMR_TKNZR_CR && tokenizer_has_next(pTokenizer)) {
            char follow_up_token = tokenizer_next_char(pTokenizer);
            if (follow_up_token == DSMR_TKNZR_LF) {
                pTelegram->data[pTelegram->amount_of_data_entries++] = telegram_data;

            }
        }

    }
    pTokenizer->current_idx--;
    return 1;
}

int _parse_checksum(Tokenizer *pTokenizer, t_telegram *pTelegram) {
    pTelegram->checksum[0] = tokenizer_next_char(pTokenizer);
    pTelegram->checksum[1] = tokenizer_next_char(pTokenizer);
    pTelegram->checksum[2] = tokenizer_next_char(pTokenizer);
    pTelegram->checksum[3] = tokenizer_next_char(pTokenizer);
    return 1;
}

void _verify_checksum(Tokenizer *pTokenizer, t_telegram *pTelegram, unsigned int range_start, unsigned int range_end) {
    for (unsigned int i = range_start; i <= range_end; ++i) {
        //TODO
    }
}


extern int DSMR_parse_data(char *data, t_telegram *result, unsigned int length) {
    Tokenizer tokenizer = tokenizer_init(data, length);
    int amount_of_telegrams_found = 0;
    while (tokenizer_has_next(&tokenizer)) {
        char current_char = tokenizer_next_char(&tokenizer);
        if (current_char == DSMR_TKNZR_START_COSEM_OBJ) {
            unsigned int start_range_checksum = tokenizer.current_idx - 1;
            printf("FF\n");
            t_telegram telegram = init_telegram();
            _read_model_specification(&tokenizer, &telegram);
            if (DSMR_TKNZR_START_IDENTIFICATION_TOKEN != tokenizer_next_char(&tokenizer)) {
                return 0;
            }
            if (!_read_model_identification(&tokenizer, &telegram)) {
                return 0;
            }
            if (!_verify_end_of_header(&tokenizer)) {
                return 0;
            }
            if (!_parse_measurements(&tokenizer, &telegram)) {
                return 0;
            }
            unsigned int end_range_checksum = tokenizer.current_idx;
            // skip !
            tokenizer_next_char(&tokenizer);
            _parse_checksum(&tokenizer, &telegram);
            _verify_checksum(&tokenizer, &telegram, start_range_checksum, end_range_checksum);
            _verify_end_of_telegram(&tokenizer);
            amount_of_telegrams_found++;
            telegram.fully_parsed = 1;
            dump_telegram(&telegram);

        }
    }
    return amount_of_telegrams_found;
}







