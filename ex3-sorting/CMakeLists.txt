cmake_minimum_required(VERSION 3.31)
project(ex3_sorting_team_44)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(ex3_sorting_team_44
        src/generator.cpp
        src/generator.h
        src/main.cpp
        src/sorting.cpp
        src/sorting.h
        tests/tests.cpp)
