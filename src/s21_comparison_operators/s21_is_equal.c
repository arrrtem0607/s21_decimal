#include "s21_header.h"

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
    s21_decimal res = {0};
    s21_normalization(&value_1, &value_2, &res);
    int result = 0;
    int sign_1 = s21_get_sign_31(value_1);
    int sign_2 = s21_get_sign_31(value_2);
    if (sign_1 == sign_2) {
        if (value_1.bits[3] == value_2.bits[3]) {
            if (value_1.bits[2] == value_2.bits[2]) {
                if (value_1.bits[1] == value_2.bits[1]) {
                    if (value_1.bits[0] == value_2.bits[0]) {
                        result = 1;
                    } else {
                        result = 0;
                    }
                } else {
                    result = 0;
                }
            } else {
                result = 0;
            }
        } else {
            result = 0;
        }
    } else {
        result = 0;
    }
    return result;
}