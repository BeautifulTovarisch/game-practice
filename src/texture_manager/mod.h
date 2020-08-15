#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <SDL2/SDL_image.h>

SDL_Texture *TM_LoadTexture(const char *asset, SDL_Renderer *renderer);

#endif
