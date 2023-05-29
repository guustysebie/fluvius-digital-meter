//
// Created by guust on 5/29/23.
//


#include <dsmr/tokenizer.h>

Tokenizer tokenizer_init(const char *data, size_t length) {
    Tokenizer tokenizer = {
            .data =data,
            .current_idx = 0,
            .length = length
    };
    return tokenizer;
}

void tokenizer_seek(Tokenizer *tokenizer, size_t idx) {
    tokenizer->current_idx = idx;
}

int tokenizer_has_next(Tokenizer *tokenizer) {
    return tokenizer->current_idx < tokenizer->length;
}

char tokenizer_next_char(Tokenizer *tokenizer) {
    return tokenizer->data[tokenizer->current_idx++];
}