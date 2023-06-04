cmake_minimum_required(VERSION 3.20)
project(fluviussm C CXX)


set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang)

set(CMAKE_C_STANDARD 99)



enable_testing()
add_subdirectory(tests)
add_subdirectory(executables)
add_subdirectory(fuzzing)
#add_subdirectory(sprite)
add_subdirectory(src)





