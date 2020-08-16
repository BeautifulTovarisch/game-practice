#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "mod.h"

#include "../robot/mod.h"

bool is_running = false;

SDL_Window *Game_Window = NULL;
SDL_Renderer *Game_Renderer = NULL;

Robot robot;

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

void Engine_Update() {
  robot.src.h = 64;
  robot.src.w = 64;

  robot.dst.h = 64;
  robot.dst.w = 64;
};

void Engine_Render() {
  SDL_RenderClear(Game_Renderer);

  Robot_Draw(robot);

  SDL_RenderPresent(Game_Renderer);
};

void Engine_Clean() {
  SDL_DestroyWindow(Game_Window);
  SDL_DestroyRenderer(Game_Renderer);
  SDL_Quit();

  printf("Cleanup complete.\n");
};

bool Engine_IsRunning() { return is_running; }
