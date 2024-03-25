cmake_minimum_required(VERSION 3.5)
project(MyProject)

set("${CMAKE_C_FLAGS} -Wall -Werror -Wextra")

add_executable(test
        test.c
        s21_help_functions.c
        s21_another_functions/s21_floor.c
        s21_another_functions/s21_round.c
        s21_another_functions/s21_negate.c
        s21_another_functions/s21_truncate.c
        s21_arithmetic_operators/s21_add.c
        s21_arithmetic_operators/s21_div.c
        s21_arithmetic_operators/s21_mul.c
        s21_arithmetic_operators/s21_sub.c
        #s21_comparison_operators/s21_is_equal.c
        s21_comparison_operators/s21_is_greater.c
        #s21_comparison_operators/s21_is_greater_or_equal.c
        #s21_comparison_operators/s21_is_less.c
        #s21_comparison_operators/s21_is_less_or_equal.c
        #s21_comparison_operators/s21_is_not_equal.c
        #s21_convertors_and_parsers/s21_from_decimal_to_int.c
        s21_convertors_and_parsers/s21_from_int_to_decimal.c
        s21_convertors_and_parsers/s21_from_float_to_decimal.c
        #s21_convertors_and_parsers/s21_from_decimal_to_float.c
)