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

// Advance frames of sprite if animated
static void animate(Sprite *sprite) {
  sprite->frame = (int)((SDL_GetTicks() / 100) % sprite->num_frames);
}

static void draw(Sprite *sprite, Vector pos, SDL_Renderer *renderer) {
  SDL_Rect src = {.w = sprite->width,
                  .h = sprite->height,
                  .x = sprite->width * sprite->frame,
                  .y = sprite->height * sprite->row};

  SDL_Rect dest = {
      .w = sprite->width, .h = sprite->height, .x = pos.x, .y = pos.y};

  if (sprite->animated == 1) {
    animate(sprite);
  }

  if (SDL_RenderCopyEx(renderer, sprite->texture, &src, &dest, 0, 0,
                       sprite->flipped) != 0) {
    printf("Failed to draw texture: %s\n", SDL_GetError());
  };
}

static int is_flipped(Entity e) {
  return ECS_GetComponent(e, C_VELOCITY)->component.vector.x > 0;
}

void DS_Draw(SDL_Renderer *renderer) {
  for (int entity = 1; entity <= ECS_GetEntityCount(); entity++) {
    if (ECS_HasComponent(entity, C_POSITION | C_SPRITE)) {
      Sprite *sprite = &ECS_GetComponent(entity, C_SPRITE)->component.sprite;
      Vector position = ECS_GetComponent(entity, C_POSITION)->component.vector;

      sprite->flipped = is_flipped(entity);

      draw(sprite, position, renderer);
    }
  }
}
