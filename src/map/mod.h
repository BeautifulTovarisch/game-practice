#ifndef MAP_H
#define MAP_H

#include <SDL2/SDL.h>

// Assets
const char *MAP_DIRT;
const char *MAP_GRASS;
const char *MAP_WATER;

int Map_Tiles[20][25];

SDL_Rect Map_Src;
SDL_Rect Map_Dest;

SDL_Texture *Dirt;
SDL_Texture *Grass;
SDL_Texture *Water;

void Map_Load();
void Map_Draw();

static inline void generate_map(int tiles[20][25], int lvl[20][25]);

#endif
