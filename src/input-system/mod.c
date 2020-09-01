#include "mod.h"

static int key_down(const Uint8 *key_state, SDL_Scancode key) {
  return key_state[key] && key_state[key] == 1;
}

// TODO :: Break up various inputs into small functions
static void handle_player_input(Entity player) {
  if (player == 0 || State_Get()->game != GAME_PLAY) {
    return;
  }

  const Uint8 *key_state = SDL_GetKeyboardState(0);

  // TODO :: Ensure that only one horizontal input is handled

  if (key_down(key_state, SDL_SCANCODE_LEFT)) {
    Physics_Accelerate(player, (Vector){.x = -1, .y = 0});
  }
  if (key_down(key_state, SDL_SCANCODE_RIGHT)) {
    Physics_Accelerate(player, (Vector){.x = 1, .y = 0});
  }

  Physics_ApplyFriction(player, 0.90);
}

// Pass the player entity to the physics system
// TODO :: Decide how player motion will ultimately be controlled
void Input_HandlePlayerInput(Entity player, SDL_Event event) {
  /* switch (event.type) { */
  /* case SDL_MOUSEMOTION: */
  /*   State_UpdateMousePosition( */
  /*       (Vector){.x = event.motion.x, .y = event.motion.y}); */
  /*   break; */
  /* case SDL_MOUSEBUTTONUP: */
  /*   State_UpdateMouseButton(MOUSE_RELEASE, event.button.button); */
  /*   break; */
  /* case SDL_MOUSEBUTTONDOWN: */
  /*   // Update mouse state */
  /*   State_UpdateMouseButton(MOUSE_CLICK, event.button.button); */
  /*   break; */
  /* default: */
  /*   break; */
  /* } */

  // Continuous keyboard updates (e.g. holding arrow keys)
  handle_player_input(player);
}

// Input for general actions (e.g quitting, pausing)
void Input_HandleGameInput(SDL_Event event) {
  switch (event.type) {
  case SDL_QUIT:
    State_Update(GAME_END);
    break;
  case SDL_KEYDOWN:
    switch (event.key.keysym.sym) {
    case SDLK_ESCAPE:
      // Only allow toggling menu when game is started.
      if (State_Get()->game & GAME_PLAY) {
        State_Update(MENU_TOGGLE);
        State_Update(GAME_TOGGLE_PAUSE);
      }
      break;
    }
    break;
  default:
    break;
  }
}
