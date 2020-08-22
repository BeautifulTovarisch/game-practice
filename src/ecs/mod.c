#include "mod.h"

Queue *entity_pool;

static void clear_components(World *world, Entity entity) {
  int position = entity_map[entity];

  if (world->component_mask[position] & C_POSITION) {
    world->position_components[position] =
        world->position_components[entity_count];
  }
  if (world->component_mask[position] & C_VELOCITY) {
    world->velocity_components[position] =
        world->velocity_components[entity_count];
  }
  if (world->component_mask[position] & C_APPEARANCE) {
    world->appearance_components[position] =
        world->appearance_components[entity_count];
  }
  if (world->component_mask[position] & C_SPRITE) {
    world->sprite_components[position] = world->sprite_components[entity_count];
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
  World world = (World){};

  memset(world.component_mask, C_NONE, MAX_ENTITIES);

  return world;
}

Entity ECS_CreateEntity() {
  if (entity_count == MAX_ENTITIES) {
    printf("Maximum entities (%d) reached.", MAX_ENTITIES);
    return 0;
  }

  Entity id = Queue_Dequeue(entity_pool);
  entity_count++;
  entity_map[id] = entity_count;

  return id;
}

void ECS_AddComponent(World *world, Entity entity, Component cmp) {
  int position = entity_map[entity];

  switch (cmp.type) {
  case C_SPRITE:
    world->sprite_components[position] = cmp.component.sprite;
    break;
  case C_POSITION:
    world->position_components[position] = cmp.component.vector;
    break;
  case C_VELOCITY:
    world->velocity_components[position] = cmp.component.vector;
    break;
  case C_APPEARANCE:
    world->appearance_components[position] = cmp.component.appearance;
    break;
  default:
    printf("Invalid component type: %d\n", cmp.type);
  }

  // Combine component types of entities
  world->component_mask[position] |= cmp.type;
}

/* TODO :: 'Shift' components to fill in gaps in component arrays */
/* after entity is deleted */
void ECS_DestroyEntity(World *world, Entity entity) {
  int position = entity_map[entity];

  // Queue 'freed' entity
  Queue_Enqueue(entity_pool, entity);

  clear_components(world, entity);
  world->component_mask[position] = C_NONE;

  entity_map[entity] = 0;
  entity_count--;
}

int *ECS_GetEntities() { return entity_map; }
int ECS_GetEntityCount() { return entity_count; }

void ECS_Cleanup() { free(entity_pool); }
