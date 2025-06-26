cmake_minimum_required(VERSION 3.30)
project(ex1_cplusplusintro_team_44)

set(CMAKE_CXX_STANDARD 14)

include_directories(.vscode/doctest/doctest)
include_directories(.vscode/doctest/doctest/extensions)
include_directories(.vscode/doctest/doctest/parts)
include_directories(.vscode/doctest/examples/all_features)
include_directories(.vscode/doctest/examples/combining_the_same_tests_built_differently_in_multiple_shared_objects)
include_directories(.vscode/doctest/examples/installed_doctest_cmake/dll)
include_directories(.vscode/doctest/scripts/development_only)
include_directories(.vscode/doctest/scripts/development_only/doctest)
include_directories(src)

add_executable(ex1_cplusplusintro_team_44
        src/grading_table.cpp
        src/grading_table.h
        src/grading_tasks.cpp
        src/grading_tasks.h
        src/main.cpp
        )
