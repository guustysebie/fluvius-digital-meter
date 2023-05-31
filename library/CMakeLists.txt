cmake_minimum_required(VERSION 3.20)
project(fluviussm C CXX)

set(CMAKE_C_STANDARD 99)



enable_testing()
add_subdirectory(tests)
add_subdirectory(executables)
add_subdirectory(sprite)
add_subdirectory(src)





