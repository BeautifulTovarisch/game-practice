#include "mod.h"

Queue *entity_pool;

void print_world(World *world) {
  for (int i = 0; i < 10; i++) {
    printf("Entity: %d\n", world->mask[i]);
  }
}

void ECS_Init() {
  static int entity_count = 0;
  static int entity_map[MAX_ENTITIES];

  entity_pool = Queue_Create(MAX_ENTITIES);

  for (Entity entity = 1; entity < MAX_ENTITIES; entity++) {
    Queue_Enqueue(entity_pool, entity);
  }
}

Entity ECS_CreateEntity(World *world) {
  if (entity_count == MAX_ENTITIES) {
    printf("Maximum entities (%d) reached.", MAX_ENTITIES);
    return 0;
  }

  Entity id = Queue_Dequeue(entity_pool);

  entity_count++;

  entity_map[id] = entity_count;
  world->mask[entity_count] = id;

  return id;
}

void ECS_DestroyEntity(World *world, Entity entity) {
  // Move last entity to fill 'gap'
  // Leaving mask tightly packed

  printf("Count %d\n", entity_count);
  printf("Entity %d\n", entity);

  int position = entity_map[entity];

  world->mask[position] = world->mask[entity_count];

  entity_map[entity] = 0;

  // Queue 'freed' entity
  Queue_Enqueue(entity_pool, entity);
  entity_count--;
}

void ECS_Cleanup() { free(entity_pool); };
