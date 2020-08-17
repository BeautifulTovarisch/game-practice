#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "mod.h"

#include "../ecs/mod.h"

bool is_running = false;

SDL_Window *Game_Window = NULL;
SDL_Renderer *Game_Renderer = NULL;

World world;

bool Engine_Init(const char *title, int x_pos, int y_pos, int width, int height,
                 bool fullscreen) {

  int full = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;

  // Initialize SDL, returning success or failure
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    printf("Initialization failed: %s\n", SDL_GetError());
    return false;
  }

  Game_Window = SDL_CreateWindow(title, x_pos, y_pos, width, height, full);
  if (!Game_Window) {
    printf("Window creation failed: %s\n", SDL_GetError());
    return false;
  }

  Game_Renderer = SDL_CreateRenderer(Game_Window, -1, 0);
  if (!Game_Renderer) {
    printf("Renderer creation failed: %s\n", SDL_GetError());
    return false;
  }

  SDL_SetRenderDrawColor(Game_Renderer, 255, 255, 255, 255);

  ECS_Init();

  Entity player = ECS_CreateEntity(&world);

  // id 1 -> 0

  ECS_CreateEntity(&world);

  print_world(&world);

  ECS_DestroyEntity(&world, player);

  printf("\n");

  ECS_CreateEntity(&world);

  print_world(&world);

  is_running = true;

  printf("Initialization success.\n");

  return true;
}

void Engine_Events() {
  SDL_Event event;
  SDL_PollEvent(&event);

  switch (event.type) {
  case SDL_QUIT:
    is_running = false;
    break;
  default:
    break;
  }
};

void Engine_Update(){
    //
};

void Engine_Render() {
  SDL_RenderClear(Game_Renderer);
  SDL_RenderPresent(Game_Renderer);
};

void Engine_Clean() {
  ECS_Cleanup();

  SDL_DestroyWindow(Game_Window);
  SDL_DestroyRenderer(Game_Renderer);
  SDL_Quit();

  printf("Cleanup complete.\n");
};

bool Engine_IsRunning() { return is_running; }
