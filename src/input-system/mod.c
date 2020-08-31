#include "mod.h"

static int key_down(const Uint8 *key_state, SDL_Scancode key) {
  return key_state[key] && key_state[key] == 1;
}

static void handle_keyboard(Entity player) {
  if (!player || !State_Get()->game == GAME_PLAY) {
    return;
  }

  const Uint8 *key_state = SDL_GetKeyboardState(0);

  if (key_down(key_state, SDL_SCANCODE_LEFT)) {
    Physics_Accelerate(player, (Vector){.x = -1, .y = 0});
  }
  if (key_down(key_state, SDL_SCANCODE_RIGHT)) {
    Physics_Accelerate(player, (Vector){.x = 1, .y = 0});
  }

  /* Physics_ReduceVelocity(player, 50); */
}

// Pass the player entity to the physics system
int Input_HandleEvents(SDL_Event event) {
  switch (event.type) {
  case SDL_QUIT:
    return 0;
    break;
  case SDL_MOUSEMOTION:
    State_UpdateMousePosition(
        (Vector){.x = event.motion.x, .y = event.motion.y});
    break;
  case SDL_MOUSEBUTTONUP:
    State_UpdateMouseButton(MOUSE_RELEASE, event.button.button);
    break;
  case SDL_MOUSEBUTTONDOWN:
    // Update mouse state
    State_UpdateMouseButton(MOUSE_CLICK, event.button.button);
    break;
  default:
    break;
  }

  handle_keyboard(1);

  return 1;
}
