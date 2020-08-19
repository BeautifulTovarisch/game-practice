#ifndef POSITION_H
#define POSITION_H

typedef struct Sprite {
  char *file;
} Sprite;

typedef struct Position {
  int x;
  int y;
} Position;

typedef struct Velocity {
  int x;
  int y;
} Velocity;

typedef struct Appearance {
  char *name;
} Appearance;

/* Component Mask */
/* Components are combined and assigned to an entity */
/* e.g. Player => C_POSITION|C_VELOCITY */
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
    Position position;
    Velocity velocity;
    Appearance appearance;
  } component;
} Component;

#endif
