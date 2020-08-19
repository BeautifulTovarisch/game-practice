#include "mod.h"

Queue *entity_pool;

static void clear_components(World *world, Entity entity) {
  if (world->component_mask[entity] & C_POSITION) {
    world->position_components[entity] = (Position){};
  }
  if (world->component_mask[entity] & C_VELOCITY) {
    world->velocity_components[entity] = (Velocity){};
  }
  if (world->component_mask[entity] & C_APPEARANCE) {
    world->appearance_components[entity] = (Appearance){};
  }
  if (world->component_mask[entity] & C_SPRITE) {
    world->sprite_components[entity] = (Sprite){};
  }
}

World ECS_Init() {
  static int entity_count = 0;
  static int entity_map[MAX_ENTITIES];

  entity_pool = Queue_Create(MAX_ENTITIES);

  // Populate entities and fill queue
  for (Entity entity = 1; entity < MAX_ENTITIES; entity++) {
    Queue_Enqueue(entity_pool, entity);
  }

  // TODO :: Initialize world with state
  World world;

  memset(world.component_mask, C_NONE, MAX_ENTITIES);

  return world;
}

Entity ECS_CreateEntity() {
  if (entity_count == MAX_ENTITIES) {
    printf("Maximum entities (%d) reached.", MAX_ENTITIES);
    return 0;
  }

  entity_count++;

  return Queue_Dequeue(entity_pool);
}

void ECS_AddComponent(World *world, Entity entity, Component cmp) {
  switch (cmp.type) {
  case C_POSITION:
    world->position_components[entity] = cmp.component.position;
    break;
  case C_VELOCITY:
    world->velocity_components[entity] = cmp.component.velocity;
    break;
  case C_APPEARANCE:
    world->appearance_components[entity] = cmp.component.appearance;
    break;
  default:
    printf("Invalid component type: %d\n", cmp.type);
  }

  // Combine component types of entities
  world->component_mask[entity] |= cmp.type;
}

/* TODO :: 'Shift' components to fill in gaps in component arrays */
/* after entity is deleted */
void ECS_DestroyEntity(World *world, Entity entity) {
  // Queue 'freed' entity
  Queue_Enqueue(entity_pool, entity);

  clear_components(world, entity);

  world->component_mask[entity] = C_NONE;

  entity_count--;
}

void ECS_Cleanup() { free(entity_pool); }
