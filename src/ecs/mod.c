#include "mod.h"

Queue *entity_pool;

void ECS_Init() {
  static int entity_count = 0;
  entity_pool = Queue_Create(MAX_ENTITIES);

  for (Entity entity = 1; entity < MAX_ENTITIES + 1; entity++) {
    Queue_Enqueue(entity_pool, entity);
  }
}

Entity ECS_CreateEntity(World *world) {
  if (entity_count == MAX_ENTITIES) {
    printf("Maximum entities (%d) reached.", MAX_ENTITIES);
    return 0;
  }

  Entity id = Queue_Dequeue(entity_pool);

  world->mask[id] = id;
  entity_count++;

  return id;
}

void ECS_DestroyEntity(World *world, unsigned int entity) {
  world->mask[entity] = COMPONENT_NONE;
  // Queue 'freed' entity
  Queue_Enqueue(entity_pool, entity);
  entity_count--;
}

void ECS_Cleanup() { free(entity_pool); };
