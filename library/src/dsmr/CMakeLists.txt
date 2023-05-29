
add_library(fluviussm_dsmr parser.c tokenizer.c)
include_directories(fluviussm_dsmr  include)
target_include_directories(fluviussm_dsmr PUBLIC include)
