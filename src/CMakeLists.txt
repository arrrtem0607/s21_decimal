cmake_minimum_required(VERSION 3.5)
project(MyProject)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wextra")

add_executable(test
        test.c
        s21_help_functions.c
        s21_arithmetic_operators.c
        s21_convertors_and_parsers.c
        s21_comparison_operators.c
)
