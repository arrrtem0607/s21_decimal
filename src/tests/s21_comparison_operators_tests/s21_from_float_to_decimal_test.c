#include "../s21_decimal_tests.h"
#include "../../s21_decimal.h"

int check_decimal_value(s21_decimal decimal, int expected_value, int expected_scale, int expected_sign) {
    int is_correct = 1;
    if (decimal.bits[0] != expected_value || decimal.bits[1] != 0 || decimal.bits[2] != 0) {
        is_correct = 0;
    }
    if (((decimal.bits[3] >> 16) & 0xFF) != expected_scale) {
        is_correct = 0;
    }
    if (((decimal.bits[3] >> 31) & 1) != expected_sign) {
        is_correct = 0;
    }
    return is_correct;
}

START_TEST(s21_from_float_to_decimal_test1) {
        float input = 123.456f;
        s21_decimal result;
        int status = s21_from_float_to_decimal(&result, input);
        int expected_value = 123456;
        int expected_scale = 3;
        int expected_sign = 0;

        ck_assert_int_eq(status, 0);
        ck_assert(check_decimal_value(result, expected_value, expected_scale, expected_sign));
}
END_TEST

START_TEST(s21_from_float_to_decimal_test2) {
    float input = -123.456f;
    s21_decimal result;
    int status = s21_from_float_to_decimal(&result, input);
    int expected_value = 123456;
    int expected_scale = 3;
    int expected_sign = 1;

    ck_assert_int_eq(status, 0);
    ck_assert(check_decimal_value(result, expected_value, expected_scale, expected_sign));
}
END_TEST

START_TEST(s21_from_float_to_decimal_test3) {
    float input = 0.0f;
    s21_decimal result;
    int status = s21_from_float_to_decimal(&result, input);
    int expected_value = 0;
    int expected_scale = 0;
    int expected_sign = 0;

    ck_assert_int_eq(status, 0);
    ck_assert(check_decimal_value(result, expected_value, expected_scale, expected_sign));
}
END_TEST

START_TEST(s21_from_float_to_decimal_test4) {
    float input = -0.0f;
    s21_decimal result;
    int status = s21_from_float_to_decimal(&result, input);
    int expected_value = 0;
    int expected_scale = 0;
    int expected_sign = 0;

    ck_assert_int_eq(status, 0);
    ck_assert(check_decimal_value(result, expected_value, expected_scale, expected_sign));
}
END_TEST

START_TEST(s21_from_float_to_decimal_test5) {
    float input = NAN;
    s21_decimal result;
    int status = s21_from_float_to_decimal(&result, input);
    int expected_value = 0;
    int expected_scale = 0;
    int expected_sign = 0;

    ck_assert_int_eq(status, 1);
    ck_assert(check_decimal_value(result, expected_value, expected_scale, expected_sign));
}
END_TEST

START_TEST(s21_from_float_to_decimal_test6) {
    float input = -NAN;
    s21_decimal result;
    int status = s21_from_float_to_decimal(&result, input);
    int expected_value = 0;
    int expected_scale = 0;
    int expected_sign = 0;

    ck_assert_int_eq(status, 1);
    ck_assert(check_decimal_value(result, expected_value, expected_scale, expected_sign));
}
END_TEST

START_TEST(s21_from_float_to_decimal_test7) {
    float input = INFINITY;
    s21_decimal result;
    int status = s21_from_float_to_decimal(&result, input);
    int expected_value = 0;
    int expected_scale = 0;
    int expected_sign = 0;

    ck_assert_int_eq(status, 1);
    ck_assert(check_decimal_value(result, expected_value, expected_scale, expected_sign));
}
END_TEST

START_TEST(s21_from_float_to_decimal_test8) {
    float input = -INFINITY;
    s21_decimal result;
    int status = s21_from_float_to_decimal(&result, input);
    int expected_value = 0;
    int expected_scale = 0;
    int expected_sign = 0;

    ck_assert_int_eq(status, 1);
    ck_assert(check_decimal_value(result, expected_value, expected_scale, expected_sign));
}
END_TEST

START_TEST(s21_from_float_to_decimal_test9) {
    float input = (float)MAX_DECIMAL + 1.0;
    s21_decimal result;
    int status = s21_from_float_to_decimal(&result, input);
    int expected_value = 0;
    int expected_scale = 0;
    int expected_sign = 0;

    ck_assert_int_eq(status, 1);
    ck_assert(check_decimal_value(result, expected_value, expected_scale, expected_sign));
}
END_TEST

        TCase *s21_from_float_to_decimal_tests() {
    TCase *tc = tcase_create("From Float to Decimal");
    tcase_add_test(tc, s21_from_float_to_decimal_test1);
    tcase_add_test(tc, s21_from_float_to_decimal_test2);
    // Добавление остальных тестов...
    tcase_add_test(tc, s21_from_float_to_decimal_test9);

    return tc;
}