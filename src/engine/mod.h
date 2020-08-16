#ifndef ENGINE_H
#define ENGINE_H

#include <SDL2/SDL.h>
#include <stdbool.h>

bool is_running;

SDL_Window *Game_Window;
SDL_Renderer *Game_Renderer;

bool Engine_Init(const char *title, int x_pos, int y_pos, int width, int height,
                 bool fullscreen);

void Engine_Events();

void Engine_Update();
void Engine_Render();

void Engine_Clean();

bool Engine_IsRunning();

#endif
