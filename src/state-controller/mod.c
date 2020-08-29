#include "mod.h"

static State state;

void State_Init() {
  state = (State){.game = GAME_DEFAULT,
                  .menu = MENU_OPENED,
                  .mouse = (MouseState){.buttons = 0, .position = (Vector){}}};
};

static void update_menu(Action action) {
  switch (action) {
    // TODO :: Consider unified 'toggle' menu action
  case MENU_OPEN:
    state.menu = MENU_OPENED;
    break;
  case MENU_CLOSE:
    state.menu = MENU_CLOSED;
    break;
  default:
    return;
  }
}

static void update_game(Action action) {
  switch (action) {
  case GAME_END:
    state.game = GAME_OVER;
    break;
  case GAME_PAUSE:
    state.game = GAME_PAUSED;
    break;
  case GAME_UNPAUSE:
    state.game = GAME_PLAY;
    break;
  default:
    return;
  }
}

void State_Update(Action action) {
  switch (action) {
  case MENU_OPEN:
  case MENU_CLOSE:
    update_menu(action);
    break;
  case GAME_END:
  case GAME_PAUSE:
  case GAME_UNPAUSE:
    update_game(action);
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
