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

static void draw(Sprite *sprite, Vector pos, SDL_Renderer *renderer) {
  SDL_Rect src = {.w = sprite->width,
                  .h = sprite->height,
                  .x = sprite->width * sprite->frame,
                  .y = sprite->height * sprite->row};

  SDL_Rect dest = {
      .w = sprite->width, .h = sprite->height, .x = pos.x, .y = pos.y};

  if (SDL_RenderCopyEx(renderer, sprite->texture, &src, &dest, 0, 0,
                       sprite->flipped) != 0) {
    printf("Failed to draw texture: %s\n", SDL_GetError());
  };
}

void DS_Draw(World *world, SDL_Renderer *renderer) {
  for (int i = 1; i <= ECS_GetEntityCount(); i++) {
    if (ECS_HasComponent(world, i, C_POSITION | C_SPRITE)) {
      Vector position = world->position_components[i];
      draw(&world->sprite_components[i], position, renderer);
    }
  }
}
