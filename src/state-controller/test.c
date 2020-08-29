#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>

#include <cmocka.h>

#include "mod.h"

static void test_state_init(void **state) {
  State_Init();

  State *state_obj = State_Get();

  assert_int_equal(state_obj->menu, MENU_OPENED);
  assert_int_equal(state_obj->game, GAME_DEFAULT);

  assert_int_equal(state_obj->mouse.buttons, 0);

  assert_int_equal(state_obj->mouse.position.x, 0);
  assert_int_equal(state_obj->mouse.position.y, 0);
}

int main(void) {
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(test_state_init),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}
