#include "s21_header.h"

void print_sign(s21_decimal number);
void print_decimal_in_binary(s21_decimal number);
void print_scale_ratio_16_23(s21_decimal number);
void s21_set_scale_ratio_16_23_big (int scale, s21_big_decimal *value);
void print_s21_decimal(s21_decimal number);



int main() {
    float val1;
    float val2;
    s21_decimal value_1 = {0};
    s21_decimal *value_1_ptr = &value_1;
    s21_decimal value_2 = {0};
    s21_decimal *value_2_ptr = &value_2;
    s21_decimal result = {0};
    s21_decimal *result_ptr = &result;
    scanf("%f %f", &val1, &val2);
    //printf("результат сложения флоатов = %.30f\n", val1 + val2);
    s21_from_float_to_decimal(value_1_ptr, val1);
    s21_from_float_to_decimal(value_2_ptr, val2);
    int mod;
    scanf("%d", &mod);
    if (mod == 1) {
        s21_add(value_1, value_2, result_ptr);
        printf("результат во флоатах = %.30f\n", val1 + val2);
    } else if (mod == 2) {
        s21_sub(value_1, value_2, result_ptr);
        printf("результат во флоатах = %.30f\n", val1 - val2);
    } else if (mod == 3){
        s21_mul(value_1, value_2, result_ptr);
        printf("результат во флоатах = %.30f\n", val1 * val2);
    } else if (mod == 4){
        //s21_div(value_1, value_2, result_ptr);
        printf("результат во флоатах = %.30f\n", val1 / val2);
    }
    printf("%u\n", value_1.bits[0]);
    print_scale_ratio_16_23(value_1);
    print_decimal_in_binary(value_1);

    printf("%u\n", value_2.bits[0]);
    print_scale_ratio_16_23(value_2);
    print_decimal_in_binary(value_2);

    printf("%u\n", result.bits[0]);
    print_scale_ratio_16_23(result);
    print_decimal_in_binary(result);
    print_s21_decimal(result);
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

void print_s21_decimal(s21_decimal number) {
    printf("результат в децималах = ");
    // Проверяем знак числа
    int sign = s21_get_sign_31(number);

    // Преобразуем мантиссу в десятичное число
    unsigned long long mantissa = 0;
    for (int i = 0; i < 3; i++) {
        mantissa += (unsigned long long)number.bits[i] << (32 * i);
    }

    // Получаем значение экспоненты
    int scale = (number.bits[3] >> 16) & 0xFF;

    // Выводим знак
    if (sign) {
        printf("-");
    }

    // Выводим мантиссу с учетом экспоненты
    if (scale == 0) {
        printf("%llu", mantissa);
    } else {
        unsigned long long int_part = mantissa / pow(10, scale);
        unsigned long long fractional_part = mantissa % (unsigned long long)pow(10, scale);
        printf("%llu.%0*llu", int_part, scale, fractional_part);
    }
}
