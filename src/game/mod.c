#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <unistd.h>

#include "mod.h"

bool is_running = false;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

bool Game_Init(const char *title, int x_pos, int y_pos, int width, int height,
               bool fullscreen) {

  int full = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;

  // Initialize SDL, returning success or failure
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    printf("Initialization failed: %s\n", SDL_GetError());
    return false;
  }

  window = SDL_CreateWindow(title, x_pos, y_pos, width, height, full);
  if (!window) {
    printf("Window creation failed: %s\n", SDL_GetError());
    return false;
  }

  renderer = SDL_CreateRenderer(window, -1, 0);
  if (!renderer) {
    printf("Renderer creation failed: %s\n", SDL_GetError());
    return false;
  }

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

  is_running = true;

  printf("Initializaion success.\n");

  return true;
}

void Game_Events() {
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

void Game_Update(){
    //
};

void Game_Render() {
  SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer);
};

void Game_Clean() {
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();

  printf("Cleanup complete.\n");
};

bool Game_IsRunning() { return is_running; }
