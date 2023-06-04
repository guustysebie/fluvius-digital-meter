//
// Created by guust on 5/29/23.
//

#ifndef FLUVIUSSM_TOKENIZER_H
#define FLUVIUSSM_TOKENIZER_H

#include <dsmr/types.h>


#define DSMR_TKNZR_START_COSEM_OBJ '/'
#define DSMR_TKNZR_START_IDENTIFICATION_TOKEN '5'
#define DSMR_TKNZR_END_DATA '!'
#define DSMR_TKNZR_CR '\r'
#define DSMR_TKNZR_LF '\n'


typedef struct Tokenizer {
    const char *data;
    unsigned int length;
    unsigned int current_idx;
} Tokenizer;


Tokenizer tokenizer_init(const char *data, unsigned int length);

void tokenizer_seek(Tokenizer *tokenizer, unsigned int idx);

int tokenizer_has_next(Tokenizer *tokenizer);

int tokenizer_is_at_end(Tokenizer *tokenizer);

char tokenizer_next_char(Tokenizer *tokenizer);



#endif //FLUVIUSSM_TOKENIZER_H
