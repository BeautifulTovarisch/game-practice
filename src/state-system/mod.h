#ifndef STATE_SYSTEM_H
#define STATE_SYSTEM_H

#include "../util/vector/mod.h"

typedef enum { MENU_CLOSED = 0, MENU_OPENED = 1 << 0 } MenuState;

// Buttons represented as Bitmask
typedef struct MouseState {
  int buttons;
  Vector position;
} MouseState;

typedef enum {
  GAME_DEFAULT = 0,
  GAME_PLAY = 1 << 0,
  GAME_PAUSED = 1 << 1,
  GAME_OVER = 1 << 2
} GameState;

typedef enum {
  ACTION_NONE = 0,

  MENU_OPEN = 1 << 0,
  MENU_CLOSE = 1 << 1,

  MOUSE_CLICK = 1 << 2,
  MOUSE_RELEASE = 1 << 3,

  GAME_END = 1 << 4,
  GAME_PAUSE = 1 << 5,
  GAME_UNPAUSE = 1 << 6
} Action;

// Game state
typedef struct State {
  GameState game;
  MenuState menu;
  MouseState mouse;
} State;

State *State_Get();

void State_Init();
void State_Update(Action action);

// Expose mouse update so that input handler can pass in vector
void State_UpdateMouseButton(Action action, int button);
void State_UpdateMousePosition(Vector vector);

#endif
