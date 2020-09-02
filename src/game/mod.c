#include "mod.h"

// Entity 0 is treated as a NULL id
Entity player = 0;

SDL_Window *Game_Window = NULL;
SDL_Renderer *Game_Renderer = NULL;

int Game_Init(const char *title, int x_pos, int y_pos, int width, int height,
              int flags) {

  // Initialize SDL, returning success or failure
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    printf("Initialization failed: %s\n", SDL_GetError());
    return 0;
  }

  Game_Window = SDL_CreateWindow(title, x_pos, y_pos, width, height, flags);
  if (!Game_Window) {
    printf("Window creation failed: %s\n", SDL_GetError());
    return 0;
  }

  Game_Renderer = SDL_CreateRenderer(Game_Window, -1, 0);
  if (!Game_Renderer) {
    printf("Renderer creation failed: %s\n", SDL_GetError());
    return 0;
  }

  SDL_SetRenderDrawColor(Game_Renderer, 0, 0, 0, 255);

  ECS_Init();
  State_Init();
  Menu_Init(Game_Renderer);

  player = ECS_CreateEntity();

  printf("Initialization success.\n");

  return 1;
}

void Game_Events() {
  SDL_Event event;

  State *state = State_Get();

  while (SDL_PollEvent(&event)) {
    // TODO :: Add state representing actual program exit rather than game over.
    if (state->game == GAME_OVER) {
      break;
    }

    // Unconditionally handle quit, pause, etc...
    Input_HandleGameInput(event);

    printf("Paused %d\n", state->game & GAME_PAUSED == GAME_PAUSED);
    if (state->game == GAME_DEFAULT ||
        state->game & GAME_PAUSED == GAME_PAUSED) {
      Menu_HandleInput(event);
    }

    // If the game is in the play state and not paused.
    if (state->game & GAME_PLAY == GAME_PLAY &&
        state->game & GAME_PAUSED != GAME_PAUSED) {
      Input_HandlePlayerInput(player, event);
    }
  }
}

void Game_Update() {
  if (State_Get()->game & GAME_PLAY == GAME_PLAY) {
    Physics_UpdatePosition();
  }
}

void Game_Render() {
  SDL_RenderClear(Game_Renderer);

  DS_Draw(Game_Renderer);

  // Only show the main menu when game is in default state.
  if (State_Get()->game == GAME_DEFAULT) {
    Menu_Show(Game_Renderer, M_MAIN);
  }

  if (State_Get()->game & GAME_PAUSED == GAME_PAUSED) {
    Menu_Show(Game_Renderer, M_PAUSE);
  }

  SDL_RenderPresent(Game_Renderer);
}

void Game_Clean() {
  ECS_Cleanup();

  Menu_Destroy();

  SDL_DestroyWindow(Game_Window);
  SDL_DestroyRenderer(Game_Renderer);
  SDL_Quit();

  printf("Cleanup complete.\n");
}

int Game_IsRunning() { return State_Get()->game != GAME_OVER; }
