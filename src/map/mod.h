#ifndef MAP_H
#define MAP_H

#include <SDL2/SDL.h>

int map[20][25];

SDL_Rect Map_Src;
SDL_Rect Map_Dest;

SDL_Texture *Map_Dirt;
SDL_Texture *Map_Grass;
SDL_Texture *Map_Water;

// Assets
const char *MAP_DIRT;
const char *MAP_GRASS;
const char *MAP_WATER;

#endif
