#include "mod.h"

Queue *entity_pool;

static int entity_count = 0;
static int entity_map[MAX_ENTITIES];

static World *world;

static void clear_components(Entity entity) {
  int index = entity_map[entity];

  int mask = world->component_mask[index];

  if (mask & C_POSITION) {
    world->position_components[index] =
        world->position_components[entity_count];
  }
  if (mask & C_VELOCITY) {
    world->velocity_components[index] =
        world->velocity_components[entity_count];
  }
  if (mask & C_ACCELERATION) {
    world->acceleration_components[index] =
        world->acceleration_components[entity_count];
  }
  if (mask & C_APPEARANCE) {
    world->appearance_components[index] =
        world->appearance_components[entity_count];
  }
  if (mask & C_COLLISION) {
    world->collision_components[index] =
        world->collision_components[entity_count];
  }
  if (mask & C_SPRITE) {
    world->sprite_components[index] = world->sprite_components[entity_count];
  }
}

void ECS_Init() {

  entity_pool = Queue_Create(MAX_ENTITIES);

  // Populate entities and fill queue
  for (Entity entity = 1; entity < MAX_ENTITIES; entity++) {
    Queue_Enqueue(entity_pool, entity);
  }

  world = &(World){};

  // Zero out all component types
  memset(world->component_mask, C_NONE, MAX_ENTITIES);
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

/* TODO :: 'Shift' components to fill in gaps in component arrays */
/* after entity is deleted */
void ECS_DestroyEntity(Entity entity) {
  int position = entity_map[entity];

  // Queue 'freed' entity
  Queue_Enqueue(entity_pool, entity);

  clear_components(entity);
  world->component_mask[position] = C_NONE;

  entity_map[entity] = 0;
  entity_count--;
}

void ECS_AddComponent(Entity entity, Component cmp) {
  int index = entity_map[entity];

  switch (cmp.type) {
  case C_SPRITE:
    world->sprite_components[index] = cmp.component.sprite;
    break;
  case C_POSITION:
    world->position_components[index] = cmp.component.vector;
    break;
  case C_VELOCITY:
    world->velocity_components[index] = cmp.component.vector;
    break;
  case C_COLLISION:
    world->collision_components[index] = cmp.component.collision;
    break;
  case C_ACCELERATION:
    world->acceleration_components[index] = cmp.component.vector;
    break;
  case C_APPEARANCE:
    world->appearance_components[index] = cmp.component.appearance;
    break;
  default:
    printf("Invalid component type: %d\n", cmp.type);
  }

  // Combine component types of entities
  world->component_mask[index] |= cmp.type;
}

Component *ECS_GetComponent(Entity e, ComponentType type) {
  int index = ECS_GetEntityPosition(e);

  switch (type) {
  case C_SPRITE:
    return &(Component){.component.sprite = world->sprite_components[index]};
  case C_POSITION:
    return &(Component){.component.vector = world->position_components[index]};
  case C_VELOCITY:
    return &(Component){.component.vector = world->velocity_components[index]};
  case C_COLLISION:
    return &(Component){.component.collision =
                            world->collision_components[index]};
    break;
  case C_ACCELERATION:
    return &(Component){.component.vector =
                            world->acceleration_components[index]};
    break;
  default:
    return &(Component){};
  }
}

// We only need type since an entity can only have one component of a given type
void ECS_RemoveComponent(Entity entity, ComponentType type) {
  int index = entity_map[entity];

  switch (type) {
  case C_SPRITE:
    world->sprite_components[index] = world->sprite_components[entity_count];
    break;
  case C_POSITION:
    world->position_components[index] =
        world->position_components[entity_count];
    break;
  case C_VELOCITY:
    world->velocity_components[index] =
        world->velocity_components[entity_count];
    break;
  case C_ACCELERATION:
    world->acceleration_components[index] =
        world->acceleration_components[entity_count];
    break;
  case C_APPEARANCE:
    world->appearance_components[index] =
        world->appearance_components[entity_count];
    break;
  default:
    NULL;
  }

  world->component_mask[index] &= ~type;
}

World *ECS_GetWorld() { return world; }

int ECS_GetEntityCount() { return entity_count; }
int ECS_GetEntityPosition(Entity entity) { return entity_map[entity]; }
// Check component bitmask to see if all flags are set
int ECS_HasComponent(Entity entity, int components) {
  return world->component_mask[ECS_GetEntityPosition(entity)] &
         components == components;
}

void ECS_Cleanup() {
  world = NULL;
  Queue_Destroy(&entity_pool);
}
