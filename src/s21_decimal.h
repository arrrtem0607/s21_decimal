#ifndef S21_HEADER_H
#define S21_HEADER_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define START_LOW 0
#define START_MID 32
#define START_HIGHT 64
#define START_INFO 96
#define SIGN_POS 127

#define MAX_DECIMAL powl(2.0, 96)
#define MIN_DECIMAL (-1 * MAX_DECIMAL)

#define MAX_POW 28
#define FLOAT_ACCURACY 7
#define S21_MAX_UINT 4294967295


//  Под комментариями находятся пояснения функции, которые нужно реализовать
//  Для каждого раздела функций нужно создать отдельный файл с именем s21_имя_раздела.с (например s21_arithmetic_operators.с)
//  Вспомогательные функции можно и нужно добавлять по необходимости

//gcc s21_help_functions.c s21_arithmetic_operators.c s21_convertors_and_parsers.c test.c
// бешеная команда для компиляции


// Основная структура
typedef struct s21_decimal {
  unsigned int bits[4];
} s21_decimal;

// Вспомогательная структура для подсчетов
typedef struct s21_big_decimal {
  unsigned int bits[8];
} s21_big_decimal;

// Вспомогательные функции
int s21_get_sign_31(s21_decimal value);  // возвращает знак числа
int s21_get_scale_ratio_16_23(s21_decimal value);  // возвращает коэфициент масштабирования (scale)
int s21_get_bit(s21_decimal value, int index);  // получает бит по индексу
int s21_get_bit_big(s21_big_decimal value, int index);  // получает бит по индексу
void s21_set_bit(int i, int res_value, s21_decimal* result);  // устанавливает бит по индексу
void s21_set_sign_31(int sign, s21_decimal* value);  // устанавливает знак числа
void s21_set_scale_ratio_16_23(int scale, s21_decimal* value);  // устанавливает коэфициент масштабирования (scale)
void s21_normalization(s21_decimal* number_1, s21_decimal* number_2, s21_decimal* result); //приводит к общему знаменателю
void s21_multiply_mantissa_by_10(s21_decimal *number);
int s21_copy_bigdecimal_to_decimal(s21_big_decimal src, s21_decimal* dst); //копирует из s21_big_decimal в s21_decimal и возвращает ошибку, если переполнение
int check_overflow(s21_big_decimal src); //проверяет на переполнение
int s21_add_mantissas(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);
int s21_sub_mantissas(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);
void s21_decl_to_null(s21_decimal *decl); // обнуляет decimal
void s21_set_bit_big(int pos, int bit, s21_big_decimal* result); // устанавливает бит по индексу в s21_big_decimal
s21_big_decimal s21_copy_decimal_to_bigdecimal(s21_decimal src); // копирует из s21_decimal в s21_big_decimal

// Арифметические функции
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);  // складывает два числа
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);  // вычитает два числа
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result); //умножает два числа
// int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result); //делит два числа

// Функции сравнения
int s21_is_less(s21_decimal, s21_decimal); //сравнивает два числа (меньше)
int s21_is_less_or_equal(s21_decimal, s21_decimal); //сравнивает два числа(меньше или равно)
int s21_is_greater(s21_decimal value_1, s21_decimal value_2); //сравнивает два числа (больше)
int s21_is_greater_or_equal(s21_decimal, s21_decimal); // сравнивает два числа (больше или равно)
int s21_is_equal(s21_decimal, s21_decimal); //сравнивает два числа (равно)
int s21_is_not_equal(s21_decimal, s21_decimal); // сравнивает два числа (не равно)

// Функции преобразования
int s21_from_int_to_decimal(s21_decimal* dst, int input);  // преобразует из int в s21_decimal (для ввода)
int s21_from_float_to_decimal(s21_decimal *dst, float input); // преобразует из float в s21_decimal (для ввода)
// int s21_from_decimal_to_int(s21_decimal src, int *dst) // преобразует из s21_decimal в int (для вывода)
// int s21_from_decimal_to_float(s21_decimal src, float *dst) // преобразует из s21_decimal в float (для вывода)

// Другие функции
// int s21_floor(s21_decimal value, s21_decimal *result) Округляет указанное Decimal число до ближайшего целого числа в сторону отрицательной бесконечности.
// int s21_round(s21_decimal value, s21_decimal *result) Округляет Decimal до ближайшего целого числа.
// int s21_truncate(s21_decimal value, s21_decimal *result) Возвращает целые цифры указанного Decimal числа; любые дробные цифры отбрасываются, включая конечные нули.
// int s21_negate(s21_decimal value, s21_decimal *result) Возвращает результат умножения указанного Decimal на -1.

void print_decimal_in_binary(s21_decimal value_1);
void print_bigdecimal_in_binary(s21_big_decimal number);

#endif