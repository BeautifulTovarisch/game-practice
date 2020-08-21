#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <SDL2/SDL_image.h>

#include "../ecs/components.h"

SDL_Texture *TM_LoadTexture(Sprite *sprite);

void TM_Draw(SDL_Texture *texture, Sprite *sprite);

#endif
