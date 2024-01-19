#include "s21_header.h"

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
    while (res - (float)resint){
        res *= 10;
        resint = (int)res;
        scale += 1;
    }
    s21_set_scale_ratio_16_23(scale, dst);
    dst->bits[0] = (int32_t)res;
    return 0;
}