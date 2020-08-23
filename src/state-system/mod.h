#ifndef STATE_SYSTEM_H
#define STATE_SYSTEM_H

// Game state

typedef enum { MENU_CLOSED = 0, MENU_OPENED = 1 << 0 } MenuState;

typedef enum {
  GAME_DEFAULT = 0,
  GAME_PLAY = 1 << 0,
  GAME_PAUSED = 1 << 2,
  GAME_OVER = 1 << 3
} GameState;

typedef enum {
  ACTION_NONE = 0,

  MENU_OPEN = 1 << 0,
  MENU_CLOSE = 1 << 1,

  GAME_END = 1 << 2,
  GAME_PAUSE = 1 << 3,
  GAME_UNPAUSE = 1 << 4
} Action;

typedef struct State {
  GameState game;
  MenuState menu;
} State;

void State_Init();
void State_Update(Action action);

#endif
