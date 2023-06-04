
add_executable(fluviussm_test test_util.h parser_test.c)
enable_testing()
target_link_libraries(fluviussm_test fluviussm_dsmr)
add_test(NAME fluviussm_test COMMAND   fluviussm_test)