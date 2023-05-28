cmake_minimum_required(VERSION 3.24)
project(fluviussm C)

set(CMAKE_C_STANDARD 99)

add_library(fluviussm SHARED library.c)
