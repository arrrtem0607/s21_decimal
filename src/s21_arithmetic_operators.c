#include "s21_header.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
    s21_normalization(&value_1, &value_2, result);
    int sign_1 = s21_get_sign_31(value_1);
    int sign_2 = s21_get_sign_31(value_2);
    int flag = 0;

    s21_decimal abs_value_1 = value_1;
    s21_decimal abs_value_2 = value_2;
    s21_set_sign_31(0, &abs_value_1);
    s21_set_sign_31(0, &abs_value_2);

    if (sign_1 == sign_2) {
        flag = s21_add_mantissas(value_1, value_2, result);
        if (sign_1){
            s21_set_sign_31(1, result);
        }
    } else {
        if ((sign_1 && !s21_is_greater(abs_value_2, abs_value_1)) ||
            (!sign_1 && s21_is_greater(abs_value_1, abs_value_2))) {
            flag = s21_sub_mantissas(value_1, value_2, result);
            s21_set_sign_31(sign_1, result);
        } else {
            flag = s21_sub_mantissas(value_2, value_1, result);
            s21_set_sign_31(sign_2, result);
        }
    }
    return flag;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
    s21_normalization(&value_1, &value_2, result);
    int sign_1 = s21_get_sign_31(value_1);
    int sign_2 = s21_get_sign_31(value_2);
    int flag = 0;

    s21_decimal abs_value_1 = value_1;
    s21_decimal abs_value_2 = value_2;
    s21_set_sign_31(0, &abs_value_1);
    s21_set_sign_31(0, &abs_value_2);

    if (sign_1 == sign_2) {
        if (s21_is_greater(abs_value_1, abs_value_2)) {
            flag = s21_sub_mantissas(value_1, value_2, result);
            s21_set_sign_31(sign_1, result);
        } else if (s21_is_greater(abs_value_2, abs_value_1)) {
            flag = s21_sub_mantissas(value_2, value_1, result);
            s21_set_sign_31(!sign_1, result);
        } else {
            s21_decl_to_null(result);
        }
    } else {
        // Числа имеют разные знаки
        flag = s21_add_mantissas(value_1, value_2, result);
        // Установим знак в соответствии с знаком первого числа
        s21_set_sign_31(sign_1, result);
    }
    return flag;
}

// int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
// int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);