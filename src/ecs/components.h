#ifndef COMPONENT_H
#define COMPONENT_H

#include <SDL2/SDL.h>

#include "../util/vector/mod.h"

// represents collision box
typedef struct Collision {
  Vector min;
  Vector max;
} Collision;

typedef struct Sprite {
  int row;
  int frame;
  int flipped;
  int animated;
  int num_frames;

  float width;
  float height;

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
  C_ACCELERATION = 1 << 2,
  C_APPEARANCE = 1 << 3,
  C_SPRITE = 1 << 4,
  C_COLLISION = 1 << 5
} ComponentType;

typedef union ComponentData {
  Sprite sprite;
  Vector vector;
  Collision collision;
  Appearance appearance;
} ComponentData;

typedef struct Component {
  ComponentType type;
  ComponentData component;
} Component;

#endif
