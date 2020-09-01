#ifndef MENU_CONTROLLER_H
#define MENU_CONTROLLER_H

#include <SDL2/SDL.h>

#include "../ecs/mod.h"

#include "../draw-system/mod.h"
#include "../physics-system/mod.h"
#include "../state-controller/mod.h"
#include "../util/vector/mod.h"

typedef enum { PLAY = 0, PAUSE = 1, RESUME = 2, EXIT = 3, QUIT = 4 } Buttons;

void Menu_Hide();
void Menu_Init(SDL_Renderer *renderer);
void Menu_Show(SDL_Renderer *renderer);
void Menu_HandleInput(SDL_Event event);

#endif
