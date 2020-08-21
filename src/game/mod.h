#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <stdbool.h>

bool is_running;

SDL_Window *Game_Window;
SDL_Renderer *Game_Renderer;

bool Game_Init(const char *title, int x_pos, int y_pos, int width, int height,
               int flags);

void Game_Events();

void Game_Update();
void Game_Render();

void Game_Clean();

bool Game_IsRunning();

#endif
