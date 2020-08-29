#include "mod.h"

static int key_down(const Uint8 *key_state, SDL_Scancode key) {
  return key_state[key] && key_state[key] == 1;
}

static void handle_keyboard(World *world, Entity player) {
  if (!player) {
    return;
  }

  const Uint8 *key_state = SDL_GetKeyboardState(0);

  /* if (key_down(key_state, SDL_SCANCODE_LEFT)) { */
  /*   Physics_Accelerate(world, player, (Vector){.x = -1, .y = 0}); */
  /* } */
  /* if (key_down(key_state, SDL_SCANCODE_RIGHT)) { */
  /*   Physics_Accelerate(world, player, (Vector){.x = 1, .y = 0}); */
  /* } */
  /* if (key_down(key_state, SDL_SCANCODE_UP)) { */
  /*   Physics_Accelerate(world, player, (Vector){.x = 0, .y = -1}); */
  /* } */
  /* if (key_down(key_state, SDL_SCANCODE_DOWN)) { */
  /*   Physics_Accelerate(world, player, (Vector){.x = 0, .y = 1}); */
  /* } */
}

// Pass the player entity to the physics system
int Input_HandleEvents(SDL_Event event, World *world, Entity player) {
  switch (event.type) {
  case SDL_QUIT:
    return 0;
    break;
  case SDL_MOUSEMOTION:
    State_UpdateMousePosition(
        (Vector){.x = event.motion.x, .y = event.motion.y});

    // Change velocity in direction of vector
    Physics_ChangeDirection(world, player,
                            (Vector){.x = event.motion.x, .y = event.motion.y});

    Physics_ReduceVelocity(world, player, 50);

    break;
  case SDL_MOUSEBUTTONUP:
    State_UpdateMouseButton(MOUSE_RELEASE, event.button.button);
    break;
  case SDL_MOUSEBUTTONDOWN:
    // Update mouse statep
    State_UpdateMouseButton(MOUSE_CLICK, event.button.button);
    break;
  default:
    break;
  }

  handle_keyboard(world, player);

  return 1;
}
