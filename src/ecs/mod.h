#ifndef ECS_H
#define ECS_H

#include <stdio.h>
#include <string.h>

#include "components.h"

#include "../util/queue/mod.h"
#include "../util/vector/mod.h"

#define MAX_ENTITIES 100

Queue *entity_pool;

typedef unsigned int Entity;

typedef struct World {
  int component_mask[MAX_ENTITIES];
  Sprite sprite_components[MAX_ENTITIES];
  Vector velocity_components[MAX_ENTITIES];
  Vector position_components[MAX_ENTITIES];
  Vector acceleration_components[MAX_ENTITIES];
  Collision collision_components[MAX_ENTITIES];
  Appearance appearance_components[MAX_ENTITIES];
} World;

World ECS_Init();

Entity ECS_CreateEntity();

// Return current entity_count
int ECS_GetEntityCount();
int ECS_GetEntityPosition(Entity entity);

void ECS_Cleanup();
void ECS_DestroyEntity(World *world, Entity entity);
void ECS_AddComponent(World *world, Entity entity, Component cmp);
void ECS_RemoveComponent(World *world, Entity entity, ComponentType type);

#endif
