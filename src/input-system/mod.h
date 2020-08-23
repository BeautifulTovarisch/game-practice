#ifndef INPUT_SYSTEM_H
#define INPUT_SYSTEM_H

#include <SDL2/SDL.h>

#include "../ecs/components.h"
#include "../ecs/mod.h"

#include "../physics-system/mod.h"
#include "../state-system/mod.h"

int Input_HandleEvents(SDL_Event event, World *world, Entity player);

#endif
