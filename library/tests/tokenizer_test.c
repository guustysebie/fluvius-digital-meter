//
// Created by guust on 5/28/23.
//
#include <dsmr/tokenizer.h>
#include <dsmr/types.h>
#include <assert.h>
#include "test_util.h"


int tokenizer_check_out_of_bounds_test() {
    const char data[] = {'a', 'b', 'c'};
    int length = 3;
    Tokenizer tokenizer = tokenizer_init(data, length);
    int v1 = tokenizer_has_next(&tokenizer);
    FDM_ASSERT_INT(1, 2)
    // assert(1 == v1);
    // assert('a' == tokenizer_next_char(&tokenizer));
    // assert('b' == tokenizer_next_char(&tokenizer));
    // assert('c' == tokenizer_next_char(&tokenizer));
    // assert('c' == tokenizer_next_char(&tokenizer));
    FDM_ASSERT_OK();
}

int simple_ok_test() {
    FDM_ASSERT_INT(1, 1)
    FDM_ASSERT_OK();
}

int simple_not_ok_test() {
    FDM_ASSERT_INT(1, 2)
    FDM_ASSERT_OK();
}


int simple_str_ok_test() {
    FDM_ASSERT_STR("abc", "abc")
    FDM_ASSERT_OK();
}

int simple_str_nok_test() {
    FDM_ASSERT_STR("aba", "abc")
    FDM_ASSERT_OK();
}



int main(void) {
    int result  = 0;// tokenizer_check_out_of_bounds_test();
    result &= simple_not_ok_test();
    result &= simple_ok_test();
    result &= simple_str_ok_test();
    for (int i = 0; i < 2; ++i) {
        result &= simple_str_nok_test();
    }

    return result;
}