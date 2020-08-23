#ifndef STATE_SYSTEM_H
#define STATE_SYSTEM_H

// Game state

typedef enum {
  S_NONE = 0,
} GameState;

typedef struct State {
  GameState state;
} State;

#endif
