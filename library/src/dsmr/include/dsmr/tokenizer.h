//
// Created by guust on 5/29/23.
//

#ifndef FLUVIUSSM_TOKENIZER_H
#define FLUVIUSSM_TOKENIZER_H


#include <stddef.h>

#define DSMR_TKNZR_START_COSEM_OBJ '/'
#define DSMR_TKNZR_START_IDENTIFICATION_TOKEN '5'


typedef struct Tokenizer {
    const char *data;
    size_t length;
    size_t current_idx;
} Tokenizer;


Tokenizer tokenizer_init(const char *data, size_t length);

void tokenizer_seek(Tokenizer *tokenizer, size_t idx);

int tokenizer_has_next(Tokenizer *tokenizer);

char tokenizer_next_char(Tokenizer *tokenizer);

#endif //FLUVIUSSM_TOKENIZER_H
