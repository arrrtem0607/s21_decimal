#include "s21_decimal.h"

void print_sign(s21_decimal number);
void print_decimal_in_binary(s21_decimal number);
void print_scale_ratio_16_23(s21_decimal number);
void print_decimal(s21_decimal number);

int main() {
    //float val1 = 0;
    //float val2 = 0;
    long val1 = 0;
    long val2 = 0;
    s21_decimal value_1 = {0};
    s21_decimal *value_1_ptr = &value_1;
    s21_decimal value_2 = {0};
    s21_decimal *value_2_ptr = &value_2;
    s21_decimal result = {0};
    s21_decimal *result_ptr = &result;
    printf("Введите число 1 и число 2 через пробел:\n");
    scanf("%ld %ld", &val1, &val2);
    //s21_from_float_to_decimal(value_1_ptr, val1);
    //s21_from_float_to_decimal(value_2_ptr, val2);
    s21_from_int_to_decimal(value_1_ptr, val1);
    s21_from_int_to_decimal(value_2_ptr, val2);
    int mod = 0;
    printf("Введите модификатор (1 - сложение, 2 - вычитание, 3 - умножение):\n");
    scanf("%d", &mod);
    if (mod == 1) {
        s21_add(value_1, value_2, result_ptr);
    } else if (mod == 2) {
        s21_sub(value_1, value_2, result_ptr);
    } else if (mod == 3) {
        s21_mul(value_1, value_2, result_ptr);
    }
    //print_sign(result);
    //printf("%u\n", result.bits[0]);
    //print_scale_ratio_16_23(result);
    print_decimal_in_binary(value_1);
    print_decimal_in_binary(value_2);
    print_decimal_in_binary(result);
    if (mod == 1){
        printf("ожидание %ld\n", val1 + val2);
    } else if (mod == 2) {
        printf("ожидание %ld\n", val1 - val2);
    } else if (mod == 3) {
        printf("ожидание %ld\n", val1 * val2);
    }
    print_decimal(result);
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

void print_decimal(s21_decimal number) {
    unsigned long long mantissa = 0;
    // Сборка мантиссы из первых трех элементов
    for (int i = 0; i < 3; i++) {
        mantissa |= ((unsigned long long)number.bits[i] << (32 * i));
    }

    // Применение масштаба
    int scale = s21_get_scale_ratio_16_23(number);
    double decimal_number = mantissa / pow(10.0, scale);

    // Применение знака
    if (s21_get_sign_31(number)) {
        decimal_number = -decimal_number;
    }

    printf("%.*lf\n", scale, decimal_number);
}