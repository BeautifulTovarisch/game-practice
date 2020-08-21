#ifndef COMPONENT_H
#define COMPONENT_H

#include <SDL2/SDL.h>

typedef struct Vector {
  float x;
  float y;
} Vector;

typedef struct Transform {
  int x;
  int y;
} Transform;

typedef struct Sprite {
  const char *file;

  Transform *transform;
  SDL_Rect src;
  SDL_Rect dest;
} Sprite;

typedef struct Velocity {
  int x;
  int y;
} Velocity;

typedef struct Appearance {
  char *name;
} Appearance;

/* Component Mask */
/* Components are combined and assigned to an entity */
/* e.g. Player => C_TRANSFORM|C_VELOCITY|C_APPEARANCE */
typedef enum {
  C_NONE = 0,
  C_TRANSFORM = 1 << 0,
  C_VELOCITY = 1 << 1,
  C_APPEARANCE = 1 << 2,
  C_SPRITE = 1 << 3
} ComponentType;

typedef struct Component {
  ComponentType type;
  union component {
    Sprite sprite;
    Transform transform;
    Velocity velocity;
    Appearance appearance;
  } component;
} Component;

#endif
