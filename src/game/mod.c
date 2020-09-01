#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "mod.h"

Entity player = 0;

SDL_Window *Game_Window = NULL;
SDL_Renderer *Game_Renderer = NULL;

bool Game_Init(const char *title, int x_pos, int y_pos, int width, int height,
               int flags) {

  // Initialize SDL, returning success or failure
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    printf("Initialization failed: %s\n", SDL_GetError());
    return false;
  }

  Game_Window = SDL_CreateWindow(title, x_pos, y_pos, width, height, flags);
  if (!Game_Window) {
    printf("Window creation failed: %s\n", SDL_GetError());
    return false;
  }

  Game_Renderer = SDL_CreateRenderer(Game_Window, -1, 0);
  if (!Game_Renderer) {
    printf("Renderer creation failed: %s\n", SDL_GetError());
    return false;
  }

  SDL_SetRenderDrawColor(Game_Renderer, 0, 0, 0, 255);

  ECS_Init();
  State_Init();
  Menu_Init(Game_Renderer);

  player = ECS_CreateEntity();

  printf("Initialization success.\n");

  return true;
}

void Game_Events() {
  SDL_Event event;

  State *state = State_Get();

  while (SDL_PollEvent(&event)) {
    if (state->game == GAME_OVER) {
      break;
    }

    printf("Paused %d\n", state->game);
    printf("Menu open %d\n", state->menu_open);

    // Unconditionally handle quit, pause, etc...
    Input_HandleGameInput(event);

    if (state->menu_open) {
      Menu_HandleInput(event);
    }

    if (state->game & GAME_PLAY == GAME_PLAY) {
      Input_HandlePlayerInput(player, event);
    }
  }
}

void Game_Update() {
  State_Get()->menu_open ? Menu_Show(Game_Renderer) : Menu_Hide();

  if (State_Get()->game == GAME_PLAY) {
    Physics_UpdatePosition();
  }
}

void Game_Render() {
  SDL_RenderClear(Game_Renderer);

  DS_Draw(Game_Renderer);

  SDL_RenderPresent(Game_Renderer);
}

void Game_Clean() {
  ECS_Cleanup();

  SDL_DestroyWindow(Game_Window);
  SDL_DestroyRenderer(Game_Renderer);
  SDL_Quit();

  printf("Cleanup complete.\n");
}

bool Game_IsRunning() { return State_Get()->game != GAME_OVER; }
