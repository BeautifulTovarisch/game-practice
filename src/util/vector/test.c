#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>

#include <cmocka.h>

#include "mod.h"

static void test_vector_add(void **state) {
  Vector result = Vector_Add(&(Vector){0}, &(Vector){1, 1});

  assert_float_equal(result.x, 1, 0);
  assert_float_equal(result.y, 1, 0);

  result = Vector_Add(&(Vector){0}, &(Vector){-1, -1});

  assert_float_equal(result.x, -1, 0);
  assert_float_equal(result.y, -1, 0);
}

static void test_vector_divide(void **state) {
  Vector input = {.x = 2, .y = 2};

  Vector result = Vector_Divide(&input, 2.0);

  assert_float_equal(result.x, 1.0, 0);
  assert_float_equal(result.y, 1.0, 0);

  // Should not allow division by 0 (defaults to 1.0)
  result = Vector_Divide(&input, 0);

  assert_float_equal(result.x, 2.0, 0);
  assert_float_equal(result.y, 2.0, 0);
};

static void test_vector_subtract(void **state) {
  Vector input = {1, 1};
  Vector result = Vector_Subtract(&input, &(Vector){1, 1});

  assert_float_equal(result.x, 0, 0);
  assert_float_equal(result.y, 0, 0);
}

static void test_vector_multiply(void **state) {
  Vector input = {1, 1};

  Vector result = Vector_Multiply(&input, 2);

  assert_float_equal(result.x, 2.0, 0);
  assert_float_equal(result.y, 2.0, 0);
}

static void test_vector_magnitude(void **state) {
  assert_float_equal(Vector_Magnitude(&(Vector){3, 4}), 5.0, 0);
}

static void test_vector_normalize(void **state) {
  Vector result = {3, 4};
  Vector_Normalize(&result);

  assert_float_equal(result.x, 0.60, 0);
  assert_float_equal(result.y, 0.80, 0);
}

int main(void) {
  const struct CMUnitTest tests[] = {cmocka_unit_test(test_vector_add),
                                     cmocka_unit_test(test_vector_divide),
                                     cmocka_unit_test(test_vector_multiply),
                                     cmocka_unit_test(test_vector_subtract),
                                     cmocka_unit_test(test_vector_magnitude),
                                     cmocka_unit_test(test_vector_normalize)};

  return cmocka_run_group_tests(tests, NULL, NULL);
}
