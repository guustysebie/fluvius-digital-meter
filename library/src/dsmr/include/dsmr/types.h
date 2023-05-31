//
// Created by guust on 5/30/23.
//

#ifndef FLUVIUSSM_TYPES_H
#define FLUVIUSSM_TYPES_H


#define true	1
#define false	0
#define bool int
#define size_t int




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

typedef struct ParsingResult {
    t_telegram telegram;
} t_parsing_result;


#endif //FLUVIUSSM_TYPES_H
