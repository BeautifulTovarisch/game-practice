#ifndef DRAW_SYSTEM_H
#define DRAW_SYSTEM_H

#include <SDL2/SDL_image.h>

#include "../ecs/components.h"
#include "../ecs/mod.h"

static void draw(Sprite *sprite);

SDL_Texture *DS_LoadTexture(const char *file);

void DS_Draw(World *world);

#endif
