#include <check.h>
#include "../lib/sed-pcre.h"

START_TEST (foo_bar) {
  ck_assert_int_eq(foo(), 0);
}
END_TEST

Suite *my_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Foo suite");

  // Core test case
  tc_core = tcase_create("Bar test case");

  tcase_add_test(tc_core, foo_bar);
  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = my_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? 0 : 1;
}
