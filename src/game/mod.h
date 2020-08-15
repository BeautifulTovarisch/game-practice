#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <stdbool.h>

extern bool is_running;

extern SDL_Window *window;
extern SDL_Renderer *renderer;

bool Game_Init(const char *title, int x_pos, int y_pos, int width, int height,
               bool fullscreen);

void Game_Events();

void Game_Update();
void Game_Render();

void Game_Clean();

bool Game_IsRunning();

#endif
