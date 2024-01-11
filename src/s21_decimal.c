#include "s21_header.h"

int main() {
  s21_decimal one = {0};
  s21_decimal two = {0};
  s21_decimal result = {0};
  s21_decimal* result_ptr = &result;
  // Тут нужна функция перевода из int в s21_decimal
  scanf(
      "%d %d", &one.bits[0],
      &two.bits[0]);  // по идее вводим int или float и переводим в s21_decimal
  // Тут нужна функция перевода из int в s21_decimal
  s21_add(one, two, result_ptr);
  printf("Result add: %d%d%d%d\n", result.bits[0], result.bits[1],
         result.bits[2], result.bits[3]);
  s21_sub(one, two, result_ptr);
  printf("Result sub: %d%d%d%d\n", result.bits[0], result.bits[1],
         result.bits[2], result.bits[3]);
  return 0;
}