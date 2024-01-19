#include "../s21_decimal.h"

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
    s21_decimal res = {0};
    s21_normalization(&value_1, &value_2, &res);
    int result = 0; // 0 - первое не больше второго, 1 - первое больше второго
    int sign_1 = s21_get_sign_31(value_1);
    int sign_2 = s21_get_sign_31(value_2);
    if (sign_1 != sign_2) {
        result = sign_1 ? 0 : 1;
    } else {
        for (int i = 3; i >= 0 && result == 0; i--) {
            if (value_1.bits[i] > value_2.bits[i]) {
                result = sign_1 ? 0 : 1;
            } else if (value_1.bits[i] < value_2.bits[i]) {
                result = sign_1 ? 1 : 0;
            }
        }
    }
    return result;
}