#include "../s21_decimal.h"

int s21_from_int_to_decimal(s21_decimal *dst, int input) {
    s21_decl_to_null(dst);
    (input < 0) ? s21_set_sign_31(1, dst) : s21_set_sign_31(0, dst);
    dst->bits[0] = abs(input);
    return 0;
}