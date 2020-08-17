#ifndef ECS_H
#define ECS_H
#include <stdio.h>

#include "components.h"

#include "../util/queue/mod.h"

#define MAX_ENTITIES 100

Queue *entity_pool;
static int entity_count;
static int entity_map[MAX_ENTITIES];

typedef unsigned int Entity;
typedef unsigned int ComponentType;

// Component Mask
typedef enum {
  COMPONENT_NONE = 0,
  COMPONENT_DISPLACEMENT = 1 << 0,
  COMPONENT_VELOCITY = 1 << 1,
  COMPONENT_APPEARANCE = 1 << 2
} Component;

typedef struct World {
  int mask[MAX_ENTITIES];
  Position position[MAX_ENTITIES];
  Velocity velocity[MAX_ENTITIES];
  Appearance appearance[MAX_ENTITIES];
} World;

Entity ECS_CreateEntity(World *world);

void ECS_Init();
void ECS_Cleanup();
void ECS_DestroyEntity(World *world, Entity entity);

#endif
