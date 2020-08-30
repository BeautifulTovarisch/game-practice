#ifndef DRAW_SYSTEM_H
#define DRAW_SYSTEM_H

#include <SDL2/SDL_image.h>

#include "../ecs/components.h"
#include "../ecs/mod.h"

SDL_Texture *DS_LoadTexture(const char *file, SDL_Renderer *renderer);

void DS_Draw(SDL_Renderer *renderer);

#endif
