cmake_minimum_required(VERSION 3.24)
project(fluviussm C)

set(CMAKE_C_STANDARD 99)

add_library(fluviussm SHARED lib/parser.c lib/parser.h)

add_executable(fluvisussmapp sprite/main.c)
target_link_libraries(fluvisussmapp fluviussm)

add_executable(port_reader target/read_port.c)
target_link_libraries(port_reader fluviussm)
