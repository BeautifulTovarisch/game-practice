#include "mod.h"

#include "../ecs/components.h"
#include "../game/mod.h"

SDL_Texture *TM_LoadTexture(Sprite *sprite) {
  SDL_Surface *surface = IMG_Load(sprite->file);
  SDL_Texture *texture = SDL_CreateTextureFromSurface(Game_Renderer, surface);

  SDL_FreeSurface(surface);

  if (!texture) {
    printf("Texture failed to load: %s\n", SDL_GetError());
  }

  return texture;
}

void TM_Draw(SDL_Texture *texture, Sprite *sprite) {
  if (SDL_RenderCopy(Game_Renderer, texture, &sprite->src, &sprite->dest) != 0) {
    printf("Failed to draw texture: %s\n", SDL_GetError());
  };
}
