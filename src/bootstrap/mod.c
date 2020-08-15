#include <SDL2/SDL.h>

#include "mod.h"

bool Bootstrap_init() {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    printf("SDL Initializtion failed: %s\n", SDL_GetError());
    return 1;
  }
}
