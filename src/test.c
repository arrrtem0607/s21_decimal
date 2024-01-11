#include "s21_header.h"

void print_sign(s21_decimal number);
void print_decimal_in_binary(s21_decimal number);
void print_scale_ratio_16_23(s21_decimal number);

int main() {
    //float val1 = 0;
    //float val2 = 0;
    /*int val1 = 0;
    int val2 = 0;
    s21_decimal value_1 = {0};
    s21_decimal *value_1_ptr = &value_1;
    s21_decimal value_2 = {0};
    s21_decimal *value_2_ptr = &value_2;
    s21_decimal result = {0};
    s21_decimal *result_ptr = &result;
    scanf("%d %d", &val1, &val2);
    //s21_from_float_to_decimal(value_1_ptr, val1);
    //s21_from_float_to_decimal(value_2_ptr, val2);
    s21_from_int_to_decimal(value_1_ptr, val1);
    s21_from_int_to_decimal(value_2_ptr, val2);
    int mod = 0;
    scanf("%d", &mod);
    if (mod == 1) {
        s21_add(value_1, value_2, result_ptr);
    } else if (mod == 2) {
        //s21_sub(value_1, value_2, result_ptr);
    }
    print_sign(result);
    printf("%u\n", result.bits[0]);
    print_scale_ratio_16_23(result);
    print_decimal_in_binary(value_1);
    print_decimal_in_binary(value_2);
    print_decimal_in_binary(result);*/
    float a = -1111111.6;
    float b = -0000000009999999.5;
    float c = 0000000000.0000999;
    float d = 00000000.000999;



    printf("%f\n%f\n%f\n%f", a, b, c, d);
    return 0;
}

void print_decimal_in_binary(s21_decimal number) {
    printf("Binary representation: ");
    for (int i = 0; i < 4; i++) {  // Итерируем через каждый элемент массива bits
        for (int j = 31; j >= 0; j--) {  // Итерируем через каждый бит в элементе массива
            printf("%d", (number.bits[i] >> j) & 1);
        }
        printf(" ");  // Для разделения каждого 32-битного числа
    }
    printf("\n");
}

void print_sign(s21_decimal number) {
    s21_get_bit(number, 127) ? printf("-") : printf("");
}

void print_scale_ratio_16_23(s21_decimal number) {
    printf("Scale ratio: %d\n", s21_get_scale_ratio_16_23(number));
}