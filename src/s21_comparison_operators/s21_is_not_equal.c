#include "s21_header.h"

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
    s21_decimal res = {0};
    s21_normalization(&value_1, &value_2, &res);
    return !s21_is_equal(value_1, value_2);
}