#ifndef MENU_CONTROLLER_H
#define MENU_CONTROLLER_H

#include <SDL2/SDL.h>

#include "../ecs/mod.h"

#include "../draw-system/mod.h"
#include "../physics-system/mod.h"
#include "../state-controller/mod.h"

typedef enum { M_MAIN = 0, M_PAUSE = 1 } Menu;
typedef enum { PLAY = 0, PAUSE = 1, RESUME = 2, EXIT = 3, QUIT = 4 } Option;

typedef struct UIComponent {
  float x;
  float y;

  int width;
  int height;

  Option option;
  SDL_Texture *texture;
} UIComponent;

void Menu_Init(SDL_Renderer *renderer);
void Menu_Show(SDL_Renderer *renderer, Menu type);
void Menu_Destroy();
void Menu_HandleInput(SDL_Event event);

#endif
