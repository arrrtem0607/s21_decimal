#include "s21_header.h"

int s21_get_sign_31(s21_decimal number) {
  return s21_get_bit(number, SIGN_POS);
}

void s21_set_sign_31(int sign, s21_decimal *value) {
    s21_set_bit(SIGN_POS, sign, value);
}

void s21_set_scale_ratio_16_23 (int scale, s21_decimal *value) {
    value -> bits[3] &= 0xFF00FFFF;
    value -> bits[3] |= (scale << 16);
}

int s21_get_scale_ratio_16_23(s21_decimal number) {
  return (number.bits[3] & 0x00FF0000) >> 16;
}

int s21_get_bit(s21_decimal value, int index) {
    return (value.bits[index / 32] & (1u << (index % 32))) >> (index % 32);
}

void s21_set_bit(int pos, int bit, s21_decimal* result) {
  if ((pos / 32 < 4) && bit)
    result -> bits[pos / 32] |= (1u << (pos % 32));
  else if ((pos / 32 < 4) && !bit)
    result -> bits[pos / 32] &= ~(1u << (pos % 32));
}

void s21_set_bit_big(int pos, int bit, s21_big_decimal* result) {
    if (pos / 32 < 4 && bit)
        result -> bits[pos / 32] |= (1u << (pos % 32));
    else if (pos / 32 < 4 && !bit)
        result -> bits[pos / 32] &= ~(1u << (pos % 32));
}



int s21_copy_bigdecimal_to_decimal(s21_big_decimal src, s21_decimal *dst) {
    int flag = check_overflow(src);
  for (int i = 0; i < 3; i++) {
    dst->bits[i] = src.bits[i];
  }
  return flag;
}

int check_overflow(s21_big_decimal src) {
  int result = 0;
  for (int i = 4; i < 8; i++) {
    if (src.bits[i] != 0) {
      result = 1; //тут нужна проверка на слишком большое число или слишком маленькое, чтобы вернуть код ошибки
      break;
    }
  }
  return result;
}

int s21_add_mantissas(s21_decimal one, s21_decimal two, s21_decimal* result) {
    int remember = 0;
    int flag = 0;
    s21_big_decimal temp = {0};
    for (int i = 0; i < START_INFO; i++) {
        int value_1 = s21_get_bit(one, i);
        int value_2 = s21_get_bit(two, i);
        int res_value = (value_1 + value_2 + remember) % 2;
        if ((value_1 + value_2 + remember) > 1) {
            remember = 1;
        } else {
            remember = 0;
        }
        s21_set_bit_big(i, res_value, &temp);
    }
    flag = s21_copy_bigdecimal_to_decimal(temp, result);
    // копируем temp в result, если нет переполнения, если есть переполнение
    // (переполнение еще зависит от scale) возвращаем код ошибки
    //  тут нужна функция копирования
    return flag;  // не ноль в случае переполнения
}

int s21_sub_mantissas(s21_decimal one, s21_decimal two, s21_decimal* result) {
    int remember = 0;
    int flag = 0;  // Флаг для обработки переполнения (пока не используется)
    s21_big_decimal temp = {0};

    for (int i = 0; i < START_INFO; i++) {
        int value_1 = s21_get_bit(one, i);
        int value_2 = s21_get_bit(two, i);
        int res_value = value_1 - value_2 - remember;

        if (res_value < 0) {
            res_value += 2;
            remember = 1;
        } else {
            remember = 0;
        }

        s21_set_bit_big(i, res_value, &temp);
    }

    flag = s21_copy_bigdecimal_to_decimal(temp, result);
    // Обработка переполнения (пока не реализована)

    return flag;  // Возвращает 0, если нет переполнения
}


void s21_decl_to_null(s21_decimal *decl) {
    for (int i = 0; i < 128; ++i) {
        s21_set_bit(i, 0, decl);
    }
}

void s21_normalization(s21_decimal* number_1, s21_decimal* number_2, s21_decimal* result) {
    if (s21_get_scale_ratio_16_23(*number_1) !=
        s21_get_scale_ratio_16_23(*number_2)) {
        if (s21_get_scale_ratio_16_23(*number_1) <
            s21_get_scale_ratio_16_23(*number_2)) {
            s21_normalization(number_2, number_1, result);
        } else {
            int scale_high = s21_get_scale_ratio_16_23(*number_1);
            int scale_low = s21_get_scale_ratio_16_23(*number_2);

            while (scale_high != scale_low && !s21_get_bit(*number_2, 96)) {
                scale_low += 1;
                s21_multiply_mantissa_by_10(number_2);
            }
            s21_set_scale_ratio_16_23(scale_low,number_2);
            s21_set_scale_ratio_16_23(scale_low, result);
        }
    }
}

void s21_multiply_mantissa_by_10(s21_decimal *number) {
    unsigned int carry = 0;
    for (int i = 0; i < 3; i++) {
        unsigned long long tmp = ((unsigned long long)number->bits[i] << 3) + // x8
                                 ((unsigned long long)number->bits[i] << 1) + // x2
                                 carry; // добавляем перенос с предыдущего шага

        number->bits[i] = (unsigned int)(tmp & 0xFFFFFFFF); // сохраняем младшие 32 бита
        carry = (unsigned int)(tmp >> 32); // сохраняем старшие 32 бита как перенос
    }
}
