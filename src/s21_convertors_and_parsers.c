#include "s21_header.h"

// Функции преобразования
// int s21_from_float_to_decimal(float src, s21_decimal *dst); // преобразует из float в s21_decimal (для ввода)
// int s21_from_decimal_to_int(s21_decimal src, int *dst) преобразует из s21_decimal в int (для вывода)
// int s21_from_decimal_to_float(s21_decimal src, float *dst) преобразует из s21_decimal в float (для вывода)

int s21_from_int_to_decimal(s21_decimal *dst, int input) {
    s21_decl_to_null(dst);
    (input < 0) ? s21_set_sign_31(1, dst) : s21_set_sign_31(0, dst);
  dst->bits[0] = abs(input);
  return 0;
}

int s21_from_float_to_decimal(s21_decimal *dst, float input) {
    int flag = 0;
    s21_decl_to_null(dst);
    if (fabs(input) < powl(10.0, -1 * MAX_POW)) {
        flag = 1;
        // dst->state = S21_NULL; хз нужно ли это, по идее программа завершится с ошибкой
    } else if (input >= MAX_DECIMAL) {
        flag = 1;
        // dst->state = S21_PLUS_INF; хз нужно ли это, по идее программа завершится с ошибкой
    } else if (input <= MIN_DECIMAL) {
        flag = 1;
        // dst->state = S21_MINUS_INF; хз нужно ли это, по идее программа завершится с ошибкой
    } else {
        int scale = 0;
        if (input < 0)
            s21_set_sign_31(1, dst);
        input = fabsl(input);
        while (!(int)input && scale < MAX_POW) {
            input *= 10;
            scale++;
        }
        s21_set_scale_ratio_16_23(scale, dst);
    }
  return flag;
}