//
// Created by GuustYsebie on 31/05/2023.
//
#include <dsmr/parser.h>
#include <dsmr/tokenizer.h>
#include <stdio.h>
#include <assert.h>


void parse_single_telegram_without_data() {
    printf("=============%s=============\n", __FUNCTION__);
    char *data = "/XXX5ID\r\n\r\n!CCCC\r\n";
    int amount = DSMR_parse_data(data, NULL, 18);
    assert(amount == 1);
}


void parse_double_telegram_without_data() {
    printf("=============%s=============\n", __FUNCTION__);
    char *data = "/XXX5ID\r\n\r\n!CCCC\r\n/XXX5ID\r\n\r\n!CCCC\r\n";
    int amount = DSMR_parse_data(data, NULL, 36);
    assert(amount == 2);
}

int main(void) {
    parse_single_telegram_without_data();
    parse_double_telegram_without_data();
    return 0;
}