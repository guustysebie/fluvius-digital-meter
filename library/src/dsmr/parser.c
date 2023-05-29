//
// Created by guust on 5/28/23.
//

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "dsmr/parser.h"
#include "dsmr/tokenizer.h"


#define SPECIFICATION_CAPACITY 100
#define DATA_CAPACITY 100

typedef struct TelegramMeasurementEntry {
    char value[100];
    char unit[100];
} t_telegram_measurement_entry;

typedef struct TelegramData {
    char first[100];
    char channel[100];
    char type[100];
    t_telegram_measurement_entry entries[100];
} t_telegram_data;

typedef struct Telegram {
    char model_specification[3];
    char identification[SPECIFICATION_CAPACITY];
    t_telegram_data data[100];
} t_telegram;

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


}

t_telegram init_telegram() {
    t_telegram telegram = {
            .model_specification={'\0'},
            .identification ={'\0'},
            .data ={'\0'}
    };
    return telegram;
}

typedef struct ParsingResult {
    int has_error;

} t_parsing_result;


void parse_data(char *data, size_t length) {
    Tokenizer tokenizer = tokenizer_init(data, length);
    while (tokenizer_has_next(&tokenizer)) {
        char current_char = tokenizer_next_char(&tokenizer);
        if (current_char == DSMR_TKNZR_START_COSEM_OBJ) {
            t_telegram telegram = init_telegram();
            telegram.model_specification[0] = tokenizer_next_char(&tokenizer);
            telegram.model_specification[1] = tokenizer_next_char(&tokenizer);
            telegram.model_specification[2] = tokenizer_next_char(&tokenizer);
            if (DSMR_TKNZR_START_IDENTIFICATION_TOKEN != tokenizer_next_char(&tokenizer)) {
                //TODO: ERROR management
            }
            size_t ctr = 0;
            while (1) {
                if (ctr + 1 >= SPECIFICATION_CAPACITY) {
                    //TODO error
                }
                char token = tokenizer_next_char(&tokenizer);
                if (token == '\r') {
                    break;
                }
                telegram.identification[ctr++] = token;
            }
            tokenizer_next_char(&tokenizer);
            tokenizer_next_char(&tokenizer);
            tokenizer_next_char(&tokenizer);
            int ctr2 = 0;
            char dataBuffer[1024] = {'\0'};
            while (1) {
                if (!tokenizer_has_next(&tokenizer)) {
                    printf("Current idx: %zu\n", tokenizer.current_idx);
                    break;
                }
                char token = tokenizer_next_char(&tokenizer);
                if (token == '!') {
                    break;
                }

                if(ctr2 >= 1024){
                    printf("BIng");
                    exit(420);
                }

                dataBuffer[ctr2] = token;
                ctr2++;
                if (token == '\r' && tokenizer_next_char(&tokenizer) == '\n') {
                    //discard new line data
                    tokenizer_next_char(&tokenizer);
                    int validLine = 0;
                    for (int i = 0; i < 1024; ++i) {
                        if (dataBuffer[i] == ':') {
                            validLine = 1;
                            break;
                        }
                    }
                    if (validLine == 1) {
                        for (int i = 0; i < 1024; ++i) {
                            printf("%c", dataBuffer[i]);
                        }
                        printf("\n");
                    }
                    memset(dataBuffer, '\0', 1023);
                    ctr2 =0;
                }
            }
            // dump_telegram(&telegram);
        }
    }
    printf("Out of while\n");
}

void test_data() {
    printf("Hello from lib\n");
}
