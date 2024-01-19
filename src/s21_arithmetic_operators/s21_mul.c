#include "s21_header.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result){
    int flag;
    s21_big_decimal value_1_big = s21_copy_decimal_to_bigdecimal(value_1);
    //s21_big_decimal value_2_big = s21_copy_decimal_to_bigdecimal(value_2);
    s21_big_decimal result_big = {0};
    if (s21_get_sign_31(value_1) == s21_get_sign_31(value_2)){
        s21_set_sign_31(0, result);
    } else {
        s21_set_sign_31(1, result);
    }
    s21_set_scale_ratio_16_23(s21_get_scale_ratio_16_23(value_1) + s21_get_scale_ratio_16_23(value_2), result);
    int bit_31;
    int bit_63;
    int bit_95;
    int bit_127;
    int bit_159;
    int bit_191;
    for (int i = 0; i < START_INFO; i++){
        print_bigdecimal_in_binary(value_1_big);
        bit_31 = s21_get_bit_big(value_1_big, 31);
        bit_63 = s21_get_bit_big(value_1_big, 63);
        bit_95 = s21_get_bit_big(value_1_big, 95);
        bit_127 = s21_get_bit_big(value_1_big, 128);
        bit_159 = s21_get_bit_big(value_1_big, 160);
        bit_191 = s21_get_bit_big(value_1_big, 192);

        result_big.bits[0] += value_1_big.bits[0] * s21_get_bit(value_2, i);
        result_big.bits[1] += value_1_big.bits[1] * s21_get_bit(value_2, i);
        result_big.bits[2] += value_1_big.bits[2] * s21_get_bit(value_2, i);
        result_big.bits[3] += value_1_big.bits[3] * s21_get_bit(value_2, i);
        result_big.bits[4] += value_1_big.bits[4] * s21_get_bit(value_2, i);
        result_big.bits[5] += value_1_big.bits[5] * s21_get_bit(value_2, i);
        result_big.bits[6] += value_1_big.bits[6] * s21_get_bit(value_2, i);

        value_1_big.bits[0] <<= 1;
        value_1_big.bits[1] <<= 1;
        value_1_big.bits[2] <<= 1;
        value_1_big.bits[3] <<= 1;
        value_1_big.bits[4] <<= 1;
        value_1_big.bits[5] <<= 1;
        value_1_big.bits[6] <<= 1;
        if (bit_31) {
            s21_set_bit_big(32, 1, &value_1_big);
        }
        if (bit_63) {
            s21_set_bit_big(64, 1, &value_1_big);
        }
        if (bit_95) {
            s21_set_bit_big(96, 1, &value_1_big);
        }
        if (bit_127) {
            s21_set_bit_big(96, 1, &value_1_big);
        }
        if (bit_159) {
            s21_set_bit_big(160, 1, &value_1_big);
        }
        if (bit_191) {
            s21_set_bit_big(192, 1, &value_1_big);
        }
    }
    flag = s21_copy_bigdecimal_to_decimal(result_big, result);
    return flag;
}