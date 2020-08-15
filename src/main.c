#include <stdio.h>

#include "game/mod.h"

int main() {
  const int FPS = 60;
  const int FRAME_DELAY = 1000 / FPS;

  Uint32 frame_start;
  int frame_time;

  // Initialize graphics
  if (!Game_Init("Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800,
                 600, false)) {
    printf("Game failed to initialize: %s\n", SDL_GetError());
  }

  while (Game_IsRunning()) {

    frame_start = SDL_GetTicks();

    Game_Events();
    Game_Update();
    Game_Render();

    frame_time = SDL_GetTicks() - frame_start;

    if (FRAME_DELAY > frame_time) {
      SDL_Delay(FRAME_DELAY - frame_time);
    }
  }

  Game_Clean();
}
