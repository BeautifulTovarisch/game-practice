#include "mod.h"

#include "../engine/mod.h"

SDL_Texture *TM_LoadTexture(const char *asset) {
  SDL_Surface *surface = IMG_Load(asset);
  SDL_Texture *texture = SDL_CreateTextureFromSurface(Game_Renderer, surface);

  SDL_FreeSurface(surface);

  if (!texture) {
    printf("Texture failed to load: %s\n", SDL_GetError());
  }

  return texture;
}

void TM_Draw(SDL_Texture *texture, SDL_Rect src, SDL_Rect dst) {
  if (SDL_RenderCopy(Game_Renderer, texture, &src, &dst) != 0) {
    printf("Failed to draw texture: %s\n", SDL_GetError());
  };
}
