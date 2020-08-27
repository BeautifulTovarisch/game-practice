#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>

#include <cmocka.h>

#include "mod.h"

static void test_add_vector(void **state) {
  Vector result = Vector_Add(&(Vector){0}, &(Vector){1, 1});

  assert_float_equal(result.x, 1, 0);
  assert_float_equal(result.y, 1, 0);

  result = Vector_Add(&(Vector){0}, &(Vector){-1, -1});

  assert_float_equal(result.x, -1, 0);
  assert_float_equal(result.y, -1, 0);
}

int main(void) {
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(test_add_vector),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
