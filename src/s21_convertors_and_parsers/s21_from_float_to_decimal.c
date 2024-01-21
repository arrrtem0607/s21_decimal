#include "../s21_decimal.h"

int s21_from_float_to_decimal(s21_decimal *dst, float input) {
    s21_decl_to_null(dst);
    if (isnan(input) || isinf(input) || fabs(input) > MAX_DECIMAL)
        return 1;
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