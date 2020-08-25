#ifndef MENU_CONTROLLER_H
#define MENU_CONTROLLER_H

#include <SDL2/SDL.h>

#include "../ecs/mod.h"

#include "../draw-system/mod.h"
#include "../physics-system/mod.h"
#include "../state-controller/mod.h"
#include "../util/vector/mod.h"

typedef enum { PLAY = 0, PAUSE = 1, RESUME = 2, EXIT = 3, QUIT = 4 } Buttons;

void Menu_Init(World *world, SDL_Renderer *renderer);

// Check for vector collision between button and mouse position
void Menu_DetectSelection(World *world);

#endif
