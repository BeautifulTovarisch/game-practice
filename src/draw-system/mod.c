#include "mod.h"

SDL_Texture *DS_LoadTexture(const char *file, SDL_Renderer *renderer) {
  SDL_Surface *surface = IMG_Load(file);
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

  SDL_FreeSurface(surface);

  if (!texture) {
    printf("Texture failed to load: %s\n", SDL_GetError());
  }

  return texture;
}

static void draw(Sprite *sprite, SDL_Renderer *renderer) {
  if (SDL_RenderCopyEx(renderer, sprite->texture, &sprite->src, &sprite->dest,
                       0, 0, sprite->flipped) != 0) {
    printf("Failed to draw texture: %s\n", SDL_GetError());
  };
}

void DS_Draw(World *world, SDL_Renderer *renderer) {
  for (int i = 1; i <= ECS_GetEntityCount(); i++) {
    if (world->component_mask[i] & C_SPRITE) {
      draw(&world->sprite_components[i], renderer);
    }
  }
}
