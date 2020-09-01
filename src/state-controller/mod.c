#include "mod.h"

static State state;

void State_Init() {
  state = (State){.game = GAME_DEFAULT,
                  .menu_open = 1,
                  .mouse = (MouseState){.buttons = 0, .position = (Vector){}}};
};

void State_Update(Action action) {
  switch (action) {
  case MENU_TOGGLE:
    state.menu_open = !state.menu_open;
    break;
  case GAME_END:
    state.game = GAME_OVER;
    break;
  case GAME_START:
    state.game |= GAME_PLAY;
    break;
  case GAME_TOGGLE_PAUSE:
    state.game ^= GAME_PAUSED;
    break;
  default:
    return;
  }
}

void State_UpdateMouseButton(Action action, int button) {
  // Update current buttons pressed as bitmask
  switch (action) {
  case MOUSE_CLICK:
    state.mouse.buttons |= button;
    break;
  case MOUSE_RELEASE:
    state.mouse.buttons &= ~button;
    break;
  default:
    return;
  }
};

void State_UpdateMousePosition(Vector vector) { state.mouse.position = vector; }

State *State_Get() { return &state; }
