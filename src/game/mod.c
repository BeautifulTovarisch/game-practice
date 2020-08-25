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

  Entity play_button = ECS_CreateEntity();
  Entity exit_button = ECS_CreateEntity();

  Menu_AddButton(play_button);
  Menu_AddButton(exit_button);

  ECS_AddComponent(
      &world, play_button,
      (Component){.type = C_SPRITE,
                  .component.sprite = {
                      .texture = DS_LoadTexture("assets/play_button.png",
                                                Game_Renderer),
                      .src = {.w = 64, .h = 64},
                      .dest = {.x = 100, .y = 100, .w = 64, .h = 48}}});

  ECS_AddComponent(&world, play_button,
                   (Component){.type = C_COLLISION,
                               .component.collision = {
                                   .origin = (Vector){.x = 100, .y = 100},
                                   .height = 64,
                                   .width = 64}});

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
