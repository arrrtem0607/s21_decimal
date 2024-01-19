#include "s21_decimal_tests.h"

int main() {
    int no_failed = 0;
    Suite *s;
    SRunner *runner;

    s = suite_create("s21_decimal Suite");
    suite_add_tcase(s, s21_from_float_to_decimal_tests());
    // Добавление других тестовых кейсов, если они есть

    runner = srunner_create(s);

    srunner_run_all(runner, CK_VERBOSE);
    no_failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}