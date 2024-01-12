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
    char temp[100];
    sprintf(temp, "%f", input);
    char str[100];
    int flag = 0;
    int i = 0;
    while (i < 8){
        for (int j = 0; j < strlen(temp); j++) {
            if ((temp[j] != '0' || temp[j + 1] == '.') && flag == 0){
                flag = 1;
            }
            if (flag){
                str[i] = temp[j];
                i++;
            }
        }
    }
    int flag1 = 0;
    for (int j = 0; j < 9; j++){
        if (str[j] == '.'){
            flag1 = 1;
            break;
        }
    }
    if (flag1){
        str[8] = '\0';
    } else {
        str[7] = '\0';
    }
    strtof();
    printf("%s\n", str);
    return 0;
}


