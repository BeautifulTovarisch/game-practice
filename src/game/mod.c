#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "mod.h"

bool is_running = false;

World world;

Entity ball;

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

  world = ECS_Init();

  ball = ECS_CreateEntity();

  State_Init();
  Menu_Init(&world, Game_Renderer);

  is_running = true;

  printf("Initialization success.\n");

  return true;
}

void Game_Events() {
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    if (!Input_HandleEvents(event, &world, player)) {
      is_running = false;
      break;
    }
  }
}

void Game_Update() {
  switch (State_Get()->menu) {
  case MENU_CLOSED:
    Menu_Hide(&world);
    break;
  case MENU_OPENED:
    Menu_Show(&world, Game_Renderer);
  default:
    break;
  }

  // TODO :: Refactor into player-specific controller
  // Change velocity in direction of vector
  switch (State_Get()->game) {
  case GAME_PLAY:
    Physics_UpdatePosition(&world);
    break;
  default:
    break;
  }
}

void Game_Render() {
  SDL_RenderClear(Game_Renderer);

  DS_Draw(&world, Game_Renderer);

  SDL_RenderPresent(Game_Renderer);
}

void Game_Clean() {
  ECS_Cleanup();

  SDL_DestroyWindow(Game_Window);
  SDL_DestroyRenderer(Game_Renderer);
  SDL_Quit();

  printf("Cleanup complete.\n");
}

bool Game_IsRunning() { return is_running; }
