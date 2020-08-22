#include "mod.h"

#include "../ecs/components.h"
#include "../game/mod.h"

SDL_Texture *DS_LoadTexture(const char *file) {
  SDL_Surface *surface = IMG_Load(file);
  SDL_Texture *texture =
      SDL_CreateTextureFromSurface(Game_GetRenderer(), surface);

  SDL_FreeSurface(surface);

  if (!texture) {
    printf("Texture failed to load: %s\n", SDL_GetError());
  }

  return texture;
}

static void draw(Sprite *sprite) {
  if (SDL_RenderCopyEx(Game_GetRenderer(), sprite->texture, &sprite->src,
                       &sprite->dest, 0, 0, sprite->flipped) != 0) {
    printf("Failed to draw texture: %s\n", SDL_GetError());
  };
}

void DS_Draw(World *world) {
  for (int i = 1; i <= ECS_GetEntityCount(); i++) {
    if (world->component_mask[i] & C_SPRITE) {
      draw(&world->sprite_components[i]);
    }
  }
}
