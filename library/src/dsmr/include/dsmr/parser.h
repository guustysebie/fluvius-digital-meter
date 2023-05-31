//
// Created by guust on 5/28/23.
//

#ifndef FLUVIUSSM_PARSER_H
#define FLUVIUSSM_PARSER_H

#include <dsmr/types.h>

#define  DSMR_PARSER_CAPACITY 4096

typedef struct DSMR_Parser {
    char data_buffer[DSMR_PARSER_CAPACITY];
} DSMR_Parser;


DSMR_Parser DSMR_parser_init(void);

void DSMR_parser_new_data(char* data, size_t length);


void parse_data(char *data, size_t length);

void test_data();

#endif //FLUVIUSSM_PARSER_H
