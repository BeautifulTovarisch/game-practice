#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <stdbool.h>

#include "../ecs/components.h"
#include "../ecs/mod.h"

#include "../draw-system/mod.h"
#include "../input-system/mod.h"

bool is_running;

Entity player;

SDL_Window *Game_Window;
SDL_Renderer *Game_Renderer;

bool Game_Init(const char *title, int x_pos, int y_pos, int width, int height,
               int flags);

bool Game_IsRunning();

void Game_Events();
void Game_Update();
void Game_Render();
void Game_Clean();

#endif
