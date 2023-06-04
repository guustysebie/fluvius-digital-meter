//
// Created by guust on 5/30/23.
//

#ifndef FLUVIUSSM_TYPES_H
#define FLUVIUSSM_TYPES_H


#include <stdbool.h>

#define SPECIFICATION_CAPACITY 100
#define DSMR_DATA_CAPACITY 100
#define DSMR_MAX_PACKET_SIZE 1024
#define DSMR_PARSER_CAPACITY 4096

typedef struct Range {
    int start;
    int end;
} t_range;

typedef struct TelegramMeasurementEntry {
    char value[100];
    char unit[100];
} t_telegram_measurement_entry;

typedef struct TelegramData {
    int initialized;
    char channel[100];
    char type[100];
    //t_telegram_measurement_entry entries[100];
} t_telegram_data;

typedef struct Telegram {
    char model_specification[3];
    char identification[SPECIFICATION_CAPACITY];
    t_telegram_data data[DSMR_DATA_CAPACITY];
    int amount_of_data_entries;
    char checksum[4];
    int fully_parsed;
} t_telegram;

typedef struct ParsingResult {
    char data[1024];
    unsigned int length;
    bool valid_checksum;
} t_parsing_result;


#endif //FLUVIUSSM_TYPES_H
