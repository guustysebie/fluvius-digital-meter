
add_executable(parser_fuzzing parser_fuzzing.cpp )
target_link_libraries(parser_fuzzing PRIVATE fluviussm_dsmr)


target_compile_options(parser_fuzzing
        PRIVATE $<$<C_COMPILER_ID:Clang>:-g -O1 -fsanitize=fuzzer>
        )

target_link_libraries(parser_fuzzing
        PRIVATE $<$<C_COMPILER_ID:Clang>:-fsanitize=fuzzer>
        )