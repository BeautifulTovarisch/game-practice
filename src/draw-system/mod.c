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
  //
  return 0;
}

void DS_Draw(SDL_Renderer *renderer) {
  World *world = ECS_GetWorld();

  for (int entity = 1; entity <= ECS_GetEntityCount(); entity++) {

    int index = ECS_GetEntityPosition(entity);

    if (ECS_HasComponent(entity, C_POSITION | C_SPRITE)) {
      Vector position = world->position_components[index];
      Sprite *sprite = &world->sprite_components[index];

      sprite->flipped = is_flipped(entity);

      draw(sprite, position, renderer);

      if (ECS_HasComponent(entity, C_POSITION | C_SPRITE)) {
        Vector position = world->position_components[entity];
        draw(&world->sprite_components[entity], position, renderer);
      }
    }
  }
}
