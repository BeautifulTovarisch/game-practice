#include "mod.h"

static int key_down(const Uint8 *key_state, SDL_Scancode key) {
  return key_state[key] && key_state[key] == 1;
}

static void handle_keyboard(World *world, Entity player) {
  if (!player) {
    return;
  }

  const Uint8 *key_state = SDL_GetKeyboardState(0);

  if (key_down(key_state, SDL_SCANCODE_LEFT)) {
    Physics_ChangeVelocity(world, player, (Vector){.x = -2, .y = 0});
  }
  if (key_down(key_state, SDL_SCANCODE_RIGHT)) {
    Physics_ChangeVelocity(world, player, (Vector){.x = 2, .y = 0});
  }
  if (key_down(key_state, SDL_SCANCODE_UP)) {
    Physics_ChangeVelocity(world, player, (Vector){.x = 0, .y = -2});
  }
  if (key_down(key_state, SDL_SCANCODE_DOWN)) {
    Physics_ChangeVelocity(world, player, (Vector){.x = 0, .y = 2});
  }
}

// Pass the player entity to the physics system
int Input_HandleEvents(SDL_Event event, World *world, Entity player) {
  switch (event.type) {
  case SDL_QUIT:
    return 0;
    break;
  default:
    break;
  }

  handle_keyboard(world, player);

  return 1;
}