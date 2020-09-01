#ifndef STATE_CONTROLLER_H
#define STATE_CONTROLLER_H

#include "../util/vector/mod.h"

// Buttons represented as Bitmask
typedef struct MouseState {
  int buttons;
  Vector position;
} MouseState;

/*
 * Game state represented here as a small bitmask, allowing for combos
 * such as: GAME_PLAY|GAME_PAUSED
 */
typedef enum {
  GAME_DEFAULT = 0,
  GAME_PLAY = 1 << 0,
  GAME_PAUSED = 1 << 1,
  GAME_OVER = 1 << 2
} GameState;

typedef enum {
  ACTION_NONE = 0,

  MENU_TOGGLE = 1 << 0,

  MOUSE_CLICK = 1 << 1,
  MOUSE_RELEASE = 1 << 2,

  GAME_END = 1 << 3,
  GAME_TOGGLE_PAUSE = 1 << 4
} Action;

// Game state
typedef struct State {
  int menu_open;

  GameState game;
  MouseState mouse;
} State;

State *State_Get();

void State_Init();
void State_Update(Action action);

// Expose mouse update so that input handler can pass in vector
void State_UpdateMouseButton(Action action, int button);
void State_UpdateMousePosition(Vector vector);

#endif
