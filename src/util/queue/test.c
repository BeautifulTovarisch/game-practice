#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>

#include <cmocka.h>

#include "mod.h"

static void test_queue_create(void **state) {
  Queue *q = Queue_Create(10);

  assert_int_equal(q->capacity, 10);

  free(q);
}

static void test_queue_destroy(void **state) {
  Queue *q = Queue_Create(1);

  Queue_Destroy(&q);

  // Ensure pointer is set to NULL to prevent use after free.
  // (or deterministically crash if attempted)
  assert_null(q);
}

static void test_queue_enqueue(void **state) {
  Queue *q = Queue_Create(3);

  Queue_Enqueue(q, 1);
  Queue_Enqueue(q, 2);
  Queue_Enqueue(q, 3);

  assert_int_equal(q->size, 3);
  assert_int_equal(q->items[q->front], 1);
  assert_int_equal(q->items[q->back], 3);

  Queue_Enqueue(q, 4);

  // Queueing past the capacity should do nothing
  assert_int_equal(q->size, 3);
  assert_int_equal(q->items[q->back], 3);

  free(q);
}

static void test_queue_dequeue(void **state) {
  Queue *q = Queue_Create(3);

  // Initialize manually to avoid dependency on enqueue function
  q->back = 2;
  q->size = 3;
  q->items = (int[]){3, 2, 1};

  assert_int_equal(Queue_Dequeue(q), 3);
  assert_int_equal(Queue_Dequeue(q), 2);
  assert_int_equal(Queue_Dequeue(q), 1);

  assert_int_equal(q->size, 0);

  assert_int_equal(Queue_Dequeue(q), INT_MIN);
}

int main(void) {
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(test_queue_create),
      cmocka_unit_test(test_queue_destroy),
      cmocka_unit_test(test_queue_enqueue),
      cmocka_unit_test(test_queue_dequeue),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
