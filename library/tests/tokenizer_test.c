//
// Created by guust on 5/28/23.
//
#include <dsmr/tokenizer.h>
#include <assert.h>
#include <stdio.h>


void tokenizer_check_out_of_bounds_test() {
    const char data[] = {'a','b','c'};
    long length = 3;
    Tokenizer tokenizer = tokenizer_init(data, length);
    int v1 = tokenizer_has_next(&tokenizer);
    assert(1 == v1);
    assert('a' == tokenizer_next_char(&tokenizer));
    assert('b' == tokenizer_next_char(&tokenizer));
    assert('c' == tokenizer_next_char(&tokenizer));
    assert('c' == tokenizer_next_char(&tokenizer));
}


int main(int argc, char **argv) {
    tokenizer_check_out_of_bounds_test();
}