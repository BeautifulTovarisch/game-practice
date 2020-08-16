#include <stdio.h>

#include "engine/mod.h"

int main() {
  const int FPS = 60;
  const int FRAME_DELAY = 1000 / FPS;

  Uint32 frame_start;
  int frame_time;

  // Initialize graphics
  if (!Engine_Init("Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                   800, 600, false)) {
    printf("Engine failed to initialize: %s\n", SDL_GetError());
  }

  while (Engine_IsRunning()) {

    frame_start = SDL_GetTicks();

    Engine_Events();
    Engine_Update();
    Engine_Render();

    frame_time = SDL_GetTicks() - frame_start;

    if (FRAME_DELAY > frame_time) {
      SDL_Delay(FRAME_DELAY - frame_time);
    }
  }

  Engine_Clean();
}
