#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "mod.h"

bool is_running = false;

World world;

Entity player;

SDL_Window *Game_Window = NULL;
SDL_Renderer *Game_Renderer = NULL;

World *Game_GetWorld() { return &world; }

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

  player = ECS_CreateEntity();

  ECS_AddComponent(
      &world, player,
      (Component){.type = C_POSITION,
                  .component.vector = (Vector){.x = 82.5, .y = 67.5}});

  ECS_AddComponent(
      &world, player,
      (Component){.type = C_VELOCITY, .component.vector = (Vector){0}});

  ECS_AddComponent(
      &world, player,
      (Component){.type = C_ACCELERATION, .component.vector = (Vector){0}});

  ECS_AddComponent(
      &world, player,
      (Component){.type = C_SPRITE,
                  .component.sprite = {
                      .texture = DS_LoadTexture("assets/horse_idle_cycle.png",
                                                Game_Renderer),
                      .width = 82,
                      .height = 66}});

  Menu_Init(&world, Game_Renderer);

  is_running = true;

  printf("Initialization success.\n");

  return true;
}

void Game_Events() {
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    if (!Input_HandleEvents(event, &world, player)) {
      is_running = false;
      break;
    };
  };
};

void Game_Update() {
  //
  Menu_DetectSelection(&world);
};

void Game_Render() {
  SDL_RenderClear(Game_Renderer);

  DS_Draw(&world, Game_Renderer);
  Physics_UpdatePosition(&world);

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
