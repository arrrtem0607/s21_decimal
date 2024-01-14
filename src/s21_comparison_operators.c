#include "s21_header.h"
// Функции сравнения
// int s21_is_less(s21_decimal, s21_decimal) // сравнивает два числа (меньше)++++
//посмотреть проверки на ноль сделать 
int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
    int result = 0; // 0 - первое не меньше второго, 1 - первое меньше второго 
    int sign_1 = s21_get_sign_31(value_1);
    int sign_2 = s21_get_sign_31(value_2);
    if (sign_2 != sign_1) {
         result = sign_1 ? 1 : 0;
    } else {
        for (int i = 3; i >= 0 && result == 0; i--) {
            if (value_1.bits[i] < value_2.bits[i]) {
                result = sign_1 ? 0 : 1;
            } else if (value_1.bits[i] > value_2.bits[i]) {
                result = sign_1 ? 1 : 0;
            }
        }
    }
    return result;
    
}

// int s21_is_less_or_equal(s21_decimal, s21_decimal) // сравнивает два числа (меньше или равно)++++
// int s21_is_greater(s21_decimal, s21_decimal) // сравнивает два числа (больше)+++++


int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
    int result = 0; // 0 - первое не больше второго, 1 - первое больше второго
    int sign_1 = s21_get_sign_31(value_1);
    int sign_2 = s21_get_sign_31(value_2);
    if (sign_1 != sign_2) {
        result = sign_1 ? 0 : 1;
    } else {
        for (int i = 3; i >= 0 && result == 0; i--) {
            if (value_1.bits[i] > value_2.bits[i]) {
                result = sign_1 ? 0 : 1;
            } else if (value_1.bits[i] < value_2.bits[i]) {
                result = sign_1 ? 1 : 0;
            }
        }
    }
    return result;
}
//первое меньше второго 

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return (s21_is_less(value_1, value_2) || s21_is_equal(value_1, value_2));
}

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {// первый вариант
  int result = 0; 
    int sign_1 = s21_get_sign_31(value_1);
    int sign_2 = s21_get_sign_31(value_2);
  if (sign_1 == sign_2) {
    if (value_1.bits[3] == value_2.bits[3]) {
      if (value_1.bits[2] == value_2.bits[2]) {
        if (value_1.bits[1] == value_2.bits[1]) {
          if (value_1.bits[0] == value_2.bits[0]) {
            result = 1;
          } else {
            result = 0;
          }
        } else {
          result = 0;
        }
      } else {
        result = 0;
      }
      } else {
        result = 0;
      }
      } else {
        result = 0;
      }
      return result;
    }
//0 false 1 true

  /*int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
    int result = 0; //0- неравны 1-равны
    int sign_1 = s21_get_sign_31(value_1);
    int sign_2 = s21_get_sign_31(value_2);
    if (sign_1 != sign_2) {
        result = 0;}
        else{
    for (int i = 3; i >= 0 && result == 0; i--) {
            if (value_1.bits[i] == value_2.bits[i]) {
                result = sign_1 ? 0 : 1;
            } else if (value_1.bits[i] != value_2.bits[i]) {
                result = 0;
            }
        }
        }
    return result;
  }
  */

  int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return (s21_is_greater(value_1, value_2) || s21_is_equal(value_1, value_2));
}

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  return !s21_is_equal(value_1, value_2);
}
// int s21_is_greater_or_equal(s21_decimal, s21_decimal) сравнивает два числа (больше или равно)+++++++++
// int s21_is_equal(s21_decimal,s21_decimal) // сравнивает два числа (равно)++++++++++
// int s21_is_not_equal(s21_decimal, s21_decimal) // сравнивает два числа (не равно)\+++++++++++++
