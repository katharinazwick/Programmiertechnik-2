cmake_minimum_required(VERSION 3.30)
project(ex2_datastructures_team_44)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(ex2_datastructures_team_44
        src/arithmetic.cpp
        src/coins.cpp
        src/Queue.h
        src/repl.cpp
        src/Set.h
        src/set_operations.cpp
        src/Stack.h
        tests/test_arithmetic.cpp
        tests/test_set_impl.cpp
        tests/test_set_operations.cpp
        tests/test_stack_impl.cpp
        tests/tests.cpp)
