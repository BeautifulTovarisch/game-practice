#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "mod.h"

#include "../ecs/mod.h"
#include "../texture_manager/mod.h"

#include "../horse/mod.h"

bool is_running = false;

SDL_Window *Game_Window = NULL;
SDL_Renderer *Game_Renderer = NULL;

World world;

bool Game_Init(const char *title, int x_pos, int y_pos, int width, int height,
               int flags) {

  // Initialize SDL, returning success or failure
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    printf("Initialization failed: %s\n", SDL_GetError());
    return false;
  }

  Game_Window = SDL_CreateWindow(title, x_pos, y_pos, width, height, flags);
  if (!Game_Window) {
    printf("Window creation failed: %s\n", SDL_GetError());
    return false;
  }

  Game_Renderer = SDL_CreateRenderer(Game_Window, -1, 0);
  if (!Game_Renderer) {
    printf("Renderer creation failed: %s\n", SDL_GetError());
    return false;
  }

  SDL_SetRenderDrawColor(Game_Renderer, 255, 255, 255, 255);

  world = ECS_Init();

  Entity horse = ECS_CreateEntity();

  Component c = {.type = C_SPRITE,
                 .component.sprite = {.file = HORSE_SPRITE,
                                      .src = (SDL_Rect){.w = 82, .h = 66},
                                      .dest = (SDL_Rect){.w = 120, .h = 100}}};

  ECS_AddComponent(&world, horse, c);

  is_running = true;

  printf("Initialization success.\n");

  return true;
}

void Game_Events() {
  SDL_Event event;
  SDL_PollEvent(&event);

  switch (event.type) {
  case SDL_QUIT:
    is_running = false;
    break;
  default:
    break;
  }
};

void Game_Update() {
  Sprite *s = &world.sprite_components[1];
  s->src.x = 82 * (((SDL_GetTicks() / 100)) % 5);
};

void Game_Render() {
  SDL_RenderClear(Game_Renderer);

  Sprite s = world.sprite_components[1];

  SDL_Texture *tx = TM_LoadTexture(&s);
  TM_Draw(tx, &s);

  SDL_RenderPresent(Game_Renderer);
}

void Game_Clean() {
  ECS_Cleanup();

  SDL_DestroyWindow(Game_Window);
  SDL_DestroyRenderer(Game_Renderer);
  SDL_Quit();

  printf("Cleanup complete.\n");
};

bool Game_IsRunning() { return is_running; }
