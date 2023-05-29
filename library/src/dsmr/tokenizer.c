//
// Created by guust on 5/29/23.
//


#include <dsmr/tokenizer.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
    bool f = tokenizer->current_idx < tokenizer->length;
    return f;
}

int tokenizer_is_at_end(Tokenizer *tokenizer){
    return tokenizer->current_idx >= tokenizer->length;
}


char tokenizer_next_char(Tokenizer *tokenizer) {
    if (tokenizer_is_at_end(tokenizer)) {
        fprintf(stderr, "tokenizer_next_char called out of range\n");
        return tokenizer->data[tokenizer->current_idx - 1];
    }
    return tokenizer->data[tokenizer->current_idx++];
}