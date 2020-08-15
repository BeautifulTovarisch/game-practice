#include <stdio.h>

#include "game/mod.h"

int main() {
  // Initialize graphics
  if (!Game_init("Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800,
                 600, false)) {
    printf("Game failed to initialize: %s\n", SDL_GetError());
  }

  while (Game_is_running()) {
    Game_events();
    Game_update();
    Game_render();
  }

  Game_clean();
}
