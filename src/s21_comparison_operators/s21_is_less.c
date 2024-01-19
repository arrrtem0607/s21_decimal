#include "s21_header.h"

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
    s21_decimal res = {0};
    s21_normalization(&value_1, &value_2, &res);
    int result = 0; // 0 - первое не меньше второго, 1 - первое меньше второго
    int sign_1 = s21_get_sign_31(value_1);
    int sign_2 = s21_get_sign_31(value_2);
    if (sign_2 != sign_1) {
        result = sign_1 ? 1 : 0;
    } else {
        for (int i = 3; i >= 0 && result == 0; i--) {
            if (value_1.bits[i] < value_2.bits[i]) {
                result = sign_1 ? 0 : 1;
            } else if (value_1.bits[i] > value_2.bits[i]) {
                result = sign_1 ? 1 : 0;
            }
        }
    }
    return result;
}