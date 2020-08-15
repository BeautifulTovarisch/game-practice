#include "mod.h"

SDL_Texture *TM_LoadTexture(const char *asset, SDL_Renderer *renderer) {
  SDL_Surface *surface = IMG_Load(asset);
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

  SDL_FreeSurface(surface);

  return texture;
}
