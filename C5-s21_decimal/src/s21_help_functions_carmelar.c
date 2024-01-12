#include "s21_header.h"

/**
 * Функция s21_get_sign возвращает знак десятичного числа.
 *
 * @param number Параметр «число» имеет тип «s21_decimal», который, вероятно,
 * является пользовательским типом данных, представляющим 21-битное десятичное
 * число со знаком.
 *
 * @return знак числа s21_decimal.
 */
//  * 16 бит: Биты от 0 до 15, младшие разряды, не используются и должны быть
//  равны нулю.
//  * 8 бит: Биты с 16 по 23 должны содержать показатель степени от 0 до 28.
//  * 7 бит: Биты с 24 по 30 не используются и должны быть равны нулю.
//  * 1 бит: Бит 31 содержит знак; 0 означает положительный, а 1 означает
//  отрицательный.
//  * Итого 32 бита

int s21_get_sign_31(s21_decimal number) {
  return s21_get_bit(number, SIGN_POS);
}

void s21_set_sign_31(int sign, s21_decimal* number) {
  s21_set_bit(SIGN_POS, sign, number);
}

void s21_set_scale_ratio_16_23( s21_decimal* number, int scale) {
  number->bits[3] &= 0xFF00FFFF;
  number->bits[3] |= (scale << 16);
}

int s21_get_scale_ratio_16_23(s21_decimal number) {
  return (number.bits[3] & 0x00FF0000) >> 16;
  // вернет значимые байты с 16 по 23 с помощью маски и логического сдвига на 16
  // разрядов (получение коэффицента масштабирования = экспонент)
}


void s21_normalization(s21_decimal* number_1, s21_decimal* number_2) {
  if (s21_get_scale_ratio_16_23(*number_1) !=
      s21_get_scale_ratio_16_23(*number_2)) {
    if (s21_get_scale_ratio_16_23(*number_1) <
        s21_get_scale_ratio_16_23(*number_2)) {
      s21_normalization(number_2, number_1);
    } else {
      int s21_scale_to_high = s21_get_scale_ratio_16_23(*number_2),
          s21_scale_to_low = s21_get_scale_ratio_16_23(*number_1);
      for (; (s21_scale_to_high - s21_scale_to_low) &&
             !s21_get_bit(*number_2, 96);
           s21_scale_to_low += 1)
        s21_scale_increase(number_2, 1);
      for (; s21_scale_to_high - s21_scale_to_low; s21_scale_to_high -= 1) {
        s21_scale_decrease(number_1, s21_scale_to_high - s21_scale_to_low);
        s21_set_scale_ratio_16_23(number_1, s21_scale_to_low);
      }
    }
  }
}  //приводит к общему знаменателю

int s21_scale_increase(s21_decimal* number, int shift) {
  if (s21_get_scale_ratio_16_23(*number) + shift < 29) {
    s21_set_scale_ratio_16_23(s21_get_scale_ratio_16_23(*number) + shift, number);
    s21_decimal additional_number_1 = *number, additional_number_2 = *number;
    if (s21_add_bit(*s21_shift_to_left(&additional_number_1, 1), 
    *s21_shift_to_left(&additional_number_2, 3), number))
      s21_set_bit(number, 96, 1);
  }
  return number;
}

s21_decimal* s21_scale_decrease(s21_decimal* number, int shift) {
  for (int y = 0; y < shift; y += 1) {
    unsigned long long overflow = number->bits[2];
    for (int x = 2; x >= 0; x -= 1) {
      number->bits[x] = overflow / 10;
      overflow =
          (overflow % 10) * (S21_MAX_UINT + 1) + number->bits[x ? x - 1 : x];
    }
  }
  s21_set_scale_ratio_16_23(number,
                            (s21_get_scale_ratio_16_23(*number) - shift));
  return number;
}

void print_s21_decimal(s21_decimal num) {
    printf("Value: %08x %08x %08x %08x\n", num.bits[0], num.bits[1], num.bits[2], num.bits[3]);
}
int main() {
    // Создайте два числа s21_decimal для тестирования
    s21_decimal num1 = {{0x12345678, 0x9ABCDEF0, 0xABCDEF01, 0x23456789}};
    s21_decimal num2 = {{0xFEDCBA98, 0x76543210, 0x98765432, 0xABCDEF01}};
    
    printf("Values before:\n");
    print_s21_decimal(num1);
    print_s21_decimal(num2);

    // Вызовите функцию нормализации
    s21_normalization(&num1, &num2);

    printf("Values after:\n");
    print_s21_decimal(num1);
    print_s21_decimal(num2);

    return 0;
}



int s21_add_bit(s21_decimal number_1, s21_decimal number_2,
                s21_decimal* result) {
  int carry = 0;

  for (int i = 0; i < 96; i++) {
    int bit1 = s21_get_bit(number_1, i);
    int bit2 = s21_get_bit(number_2, i);

    int sum;

    if (bit1 == 0 && bit2 == 0) {
      sum = carry;
      carry = 0;
    } else if (bit1 != bit2) {
      sum = carry--;
    } else {
      sum = carry++;
    }

    s21_set_bit(result, i, sum);

    if (i == 95 && carry == 1 && s21_get_bit(number_1, 97) == 0 &&
        s21_get_bit(number_2, 97) == 0) {
      return 1;
    }
  }

  return 0;
}

s21_decimal* s21_shift_to_left(s21_decimal* number, int shift) {
  if (!(s21_get_last_bit(*number) + shift > 95)) {
    for (int y = 0; y < shift; y += 1) {
      int bit_to_transfer_1 = s21_get_bit(*number, 31);
      int bit_to_transfer_2 = s21_get_bit(*number, 63);
      for (int x = 0; x < 3; x += 1) number->bits[x] <<= 1;
      if (bit_to_transfer_1) s21_set_bit(number, 32, 1);
      if (bit_to_transfer_2) s21_set_bit(number, 64, 1);
    }
  }
  return number;
}

int s21_get_bit(s21_decimal number, int index) {
  return (number.bits[index / 32] & (1u << (index % 32))) >> (index % 32);
}

int s21_get_last_bit(s21_decimal number) {
  int last_bit = 95;
  for (; (last_bit >= 0) && (!s21_get_bit(number, last_bit));) last_bit -= 1;
  return last_bit;
}

void s21_set_bit(int pos, int bit, s21_decimal* result) {
  if (pos / 32 < 4 && bit)
    result->bits[pos / 32] |= (1u << (pos % 32));
  else if (pos / 32 < 4 && !bit)
    result->bits[pos / 32] &= ~(1u << (pos % 32));
}

void s21_set_bit_big(int pos, int bit, s21_big_decimal* result) {
  if (pos / 32 < 4 && bit)
    result->bits[pos / 32] |= (1u << (pos % 32));
  else if (pos / 32 < 4 && !bit)
    result->bits[pos / 32] &= ~(1u << (pos % 32));
}

int s21_copy_bigdecimal_to_decimal(s21_big_decimal src, s21_decimal* dst) {
  int flag = check_overflow(src);
  for (int i = 0; i < 4; i++) {
    dst->bits[i] = src.bits[i];
  }
  return flag;
}

int check_overflow(s21_big_decimal src) {
  int result = 0;
  for (int i = 4; i < 8; i++) {
    if (src.bits[i] != 0) {
      result = 1;  //тут нужна проверка на слишком большое число или слишком
                   //маленькое, чтобы вернуть код ошибки
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

    s21_set_bit(i, res_value, &temp);
  }

  flag = s21_copy_bigdecimal_to_decimal(temp, result);
  // Обработка переполнения (пока не реализована)

  return flag;  // Возвращает 0, если нет переполнения
}

void s21_decl_to_null(s21_decimal* decl) {
  for (int i = 0; i < 128; ++i) {
    s21_set_bit(i, 0, decl);
  }
}
