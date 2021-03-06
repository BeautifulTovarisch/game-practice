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

World *ECS_GetWorld();
Entity ECS_CreateEntity();
Component *ECS_GetComponent(Entity e, ComponentType type);

// Return current entity_count
int ECS_GetEntityCount();
int ECS_GetEntityPosition(Entity entity);
int ECS_HasComponent(Entity entity, int components);

void ECS_Init();
void ECS_Cleanup();
void ECS_DestroyEntity(Entity entity);
void ECS_AddComponent(Entity entity, Component cmp);
void ECS_RemoveComponent(Entity entity, ComponentType type);

#endif
