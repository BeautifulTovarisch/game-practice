#include "mod.h"

// Collisions are checked 'from the left'
// Reverse order of collision parameters to check other border
static int horizontal(Collision a, Collision b) {
  return a.origin.x + a.width >= b.origin.x;
}

static int vertical(Collision a, Collision b) {
  return a.origin.y + a.height >= b.origin.y;
}

int Physics_EntityCollision(Entity e_a, Entity e_b) {
  World *world = ECS_GetWorld();

  int index_a = ECS_GetEntityPosition(e_a),
      index_b = ECS_GetEntityPosition(e_b);

  // Check for possiblity of collision
  if (!(world->component_mask[index_a] & C_COLLISION) ||
      !(world->component_mask[index_b] & C_COLLISION)) {
    return 0;
  }

  // Get collision boxes
  Collision coll_a = world->collision_components[index_a],
            coll_b = world->collision_components[index_b];

  return (horizontal(coll_a, coll_b) || horizontal(coll_b, coll_a)) &&
         (vertical(coll_a, coll_b) || vertical(coll_b, coll_a));
}

// Determine if vector lies inside collision box
// e.g mouse inside button
int Physics_VectorCollision(Entity entity, Vector v) {
  World *world = ECS_GetWorld();
  int index = ECS_GetEntityPosition(entity);

  if (!(world->component_mask[index] & C_COLLISION)) {
    return 0;
  }

  Collision col = world->collision_components[index];

  return v.x >= col.origin.x && v.y >= col.origin.y &&
         v.x <= (col.origin.x + col.width) &&
         v.y <= (col.origin.y + col.height);
}

// Update position of entities with Position and Velocity vectors
void Physics_UpdatePosition() {
  World *world = ECS_GetWorld();

  for (int entity = 1; entity <= ECS_GetEntityCount(); entity++) {

    int e_pos = ECS_GetEntityPosition(entity);

    if (ECS_HasComponent(entity, (C_POSITION | C_VELOCITY | C_ACCELERATION))) {
      Vector velocity = world->velocity_components[e_pos];
      Vector position = world->position_components[e_pos];
      Vector acceleration = world->acceleration_components[e_pos];

      world->velocity_components[e_pos] = Vector_Add(&velocity, &acceleration);
      world->position_components[e_pos] = Vector_Add(&position, &velocity);

      // Apply friction/gravity

      world->acceleration_components[e_pos] =
          Vector_Multiply(&acceleration, 0.9);
    }
  }
}

void Physics_Accelerate(Entity entity, Vector v) {
  World *world = ECS_GetWorld();

  if (ECS_HasComponent(entity, C_ACCELERATION)) {
    int position = ECS_GetEntityPosition(entity);
    world->acceleration_components[position] =
        Vector_Add(&world->acceleration_components[position], &v);
  }
}

// Change direction of entity toward vector
void Physics_ChangeDirection(Entity entity, Vector v) {
  World *world = ECS_GetWorld();

  int position = ECS_GetEntityPosition(entity);

  if (ECS_HasComponent(entity, C_VELOCITY)) {
    world->velocity_components[position] =
        Vector_Subtract(&v, &world->velocity_components[position]);
  }
}
