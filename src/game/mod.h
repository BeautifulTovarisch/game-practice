#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <stdbool.h>

extern bool is_running;

extern SDL_Window *window;
extern SDL_Renderer *renderer;

bool Game_init(const char *title, int x_pos, int y_pos, int width, int height,
               bool fullscreen);

void Game_events();

void Game_update();
void Game_render();

void Game_clean();

bool Game_is_running();

#endif
