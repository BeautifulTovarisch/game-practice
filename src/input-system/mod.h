#ifndef INPUT_SYSTEM_H
#define INPUT_SYSTEM_H

#include <stdio.h>

#include <SDL2/SDL.h>

#include "../ecs/components.h"
#include "../ecs/mod.h"

#include "../physics-system/mod.h"
#include "../state-controller/mod.h"

void Input_HandleGameInput(SDL_Event event);
void Input_HandlePlayerInput(Entity player, SDL_Event event);

#endif
