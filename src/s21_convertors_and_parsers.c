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
    if (input < 0){
        s21_set_sign_31(1 ,dst);
        input *= -1;
    }
    char str[100];
    int numChars = sprintf(str, "%.*g", 7, input);
    str[numChars] = '\0';
    char* ost;
    float res = strtof(str, &ost);
    int resint = (int)res;
    int scale = 0;
    //printf("src: %.20f\n", res);
    while (res - (float)resint){
        res *= 10;
        resint = (int)res;
        scale += 1;
    }
    s21_set_scale_ratio_16_23(scale, dst);
    dst->bits[0] = res;
    //printf("mantisse: %d\n", resint);
    //printf("scale: %d\n", scale);
    return 0;
}


