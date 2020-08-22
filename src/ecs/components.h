#ifndef COMPONENT_H
#define COMPONENT_H

#include <SDL2/SDL.h>

#include "../util/vector/mod.h"

typedef struct Sprite {
  int flipped;
  const char *file;

  SDL_Rect src;
  SDL_Rect dest;
  SDL_Texture *texture;
} Sprite;

typedef struct Appearance {
  char *name;
} Appearance;

/* Component Mask */
/* Components are combined and assigned to an entity */
/* e.g. Player => C_POSITION|C_VELOCITY|C_APPEARANCE */
typedef enum {
  C_NONE = 0,
  C_POSITION = 1 << 0,
  C_VELOCITY = 1 << 1,
  C_APPEARANCE = 1 << 2,
  C_SPRITE = 1 << 3
} ComponentType;

typedef struct Component {
  ComponentType type;
  union component {
    Sprite sprite;
    Vector vector;
    Appearance appearance;
  } component;
} Component;

#endif
