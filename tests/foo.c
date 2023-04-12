#include <check.h>
#include "../lib/psed.h"

START_TEST (parse_program_test) {
  Program program = parse_program("s/foo/bar/");
  ck_assert_int_eq(program.func, SUBSTITUTE);
  ck_assert_ptr_ne(program.pattern, NULL);
  ck_assert_ptr_ne(program.replacement, NULL);
} END_TEST

Suite *my_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Foo suite");

  // Core test case
  tc_core = tcase_create("Bar test case");

  tcase_add_test(tc_core, parse_program_test);
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
