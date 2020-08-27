#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>

#include <cmocka.h>

#include "mod.h"

static void stub_test(void **state) { (void)state; }

int main(void) {
  const struct CMUnitTest tests[] = {cmocka_unit_test(stub_test)};

  Vector result = Vector_Add(&(Vector){0}, &(Vector){1, 1});

  assert_float_equal(result.x, 1, 0);
  assert_float_equal(result.y, 1, 0);

  return cmocka_run_group_tests(tests, NULL, NULL);
}
