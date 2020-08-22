#ifndef ECS_H
#define ECS_H

#include <stdio.h>
#include <string.h>

#include "components.h"

#include "../util/queue/mod.h"

#define MAX_ENTITIES 100

Queue *entity_pool;

static int entity_count;
static int entity_map[MAX_ENTITIES];

typedef unsigned int Entity;

typedef struct World {
  int component_mask[MAX_ENTITIES];
  Sprite sprite_components[MAX_ENTITIES];
  Velocity velocity_components[MAX_ENTITIES];
  Transform transform_components[MAX_ENTITIES];
  Appearance appearance_components[MAX_ENTITIES];
} World;

static void clear_components(World *world, Entity entity);

World ECS_Init();

Entity ECS_CreateEntity();

// Return current entity_count
int ECS_GetEntityCount();

void ECS_Cleanup();
void ECS_DestroyEntity(World *world, Entity entity);
void ECS_AddComponent(World *world, Entity entity, Component cmp);

#endif
