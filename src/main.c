#include <SDL2/SDL.h>
#include <stdio.h>

const int SCR_W = 640;
const int SCR_H = 480;

int main() {
  // Initialize graphics
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    printf("Error initializing SDL: %s\n", SDL_GetError());
    return 1;
  }

  SDL_Window *window = NULL;
  SDL_Surface *surface = NULL;

  window =
      SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,
                       SDL_WINDOWPOS_UNDEFINED, SCR_W, SCR_H, SDL_WINDOW_SHOWN);

  if (!window) {
    printf("Window could not be created. SDL Error: %s\n", SDL_GetError());
    return 1;
  }

  surface = SDL_GetWindowSurface(window);

  SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));

  SDL_UpdateWindowSurface(window);
  SDL_Delay(2000);

  // Cleanup
  SDL_DestroyWindow(window);
  SDL_Quit();
}
