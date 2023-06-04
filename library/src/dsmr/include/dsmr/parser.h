//
// Created by guust on 5/28/23.
//

#ifndef FLUVIUSSM_PARSER_H
#define FLUVIUSSM_PARSER_H

#include <dsmr/types.h>


typedef struct DSMR_Parser {
    char data_buffer[DSMR_PARSER_CAPACITY];
    unsigned int current_idx;
} DSMR_Parser;


DSMR_Parser DSMR_parser_init(void (*complete_message)(t_parsing_result));

void DSMR_parser_add_bytes(DSMR_Parser *parser, char *data, unsigned int length);
int DSMR_parse_current_buffer(DSMR_Parser *parser, t_parsing_result* result_array);


int DSMR_parse_data(char *data, t_telegram* result, unsigned int length);

void test_data();

#endif //FLUVIUSSM_PARSER_H
