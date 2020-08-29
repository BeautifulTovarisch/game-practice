#include "mod.h"

// Collisions are checked 'from the left'
// Reverse order of collision parameters to check other border
static int horizontal(Collision a, Collision b) {
  return a.origin.x + a.width >= b.origin.x;
}

static int vertical(Collision a, Collision b) {
  return a.origin.y + a.height >= b.origin.y;
}

int Physics_EntityCollision(World *world, Entity e_a, Entity e_b) {
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
int Physics_VectorCollision(World *world, Entity entity, Vector v) {
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
void Physics_UpdatePosition(World *world) {
  for (int entity = 1; entity <= ECS_GetEntityCount(); entity++) {

    int e_pos = ECS_GetEntityPosition(entity);

    if (ECS_HasComponent(world, entity,
                         (C_POSITION | C_VELOCITY | C_ACCELERATION))) {
      Vector velocity = world->velocity_components[e_pos];
      Vector position = world->position_components[e_pos];
      Vector acceleration = world->acceleration_components[e_pos];

      world->velocity_components[e_pos] = Vector_Add(&velocity, &acceleration);
      world->position_components[e_pos] = Vector_Add(&position, &velocity);
    }

    /* if (ECS_HasComponent(world, entity, (C_POSITION | C_SPRITE))) { */
    /*   Sprite *sprite = &world->sprite_components[e_pos]; */

    /*   sprite->dest.x = world->position_components[e_pos].x; */
    /*   sprite->dest.y = world->position_components[e_pos].y; */
    /* } */
  }
}

void Physics_Accelerate(World *world, Entity entity, Vector v) {
  if (ECS_HasComponent(world, entity, C_ACCELERATION)) {
    int position = ECS_GetEntityPosition(entity);
    world->acceleration_components[position] =
        Vector_Add(&world->acceleration_components[position], &v);
  }
}

// Add vector to velocity to increase/decrease
void Physics_ChangeVelocity(World *world, Entity entity, Vector v) {
  // Do nothing if entity hasn't registered a velocity component
  if (ECS_HasComponent(world, entity, C_VELOCITY)) {
    int position = ECS_GetEntityPosition(entity);
    world->velocity_components[position] =
        Vector_Add(&world->velocity_components[position], &v);
  }
}

// Divide velocity by scalar
void Physics_ReduceVelocity(World *world, Entity entity, float scl) {
  if (ECS_HasComponent(world, entity, C_VELOCITY)) {
    int position = ECS_GetEntityPosition(entity);
    world->velocity_components[position] =
        Vector_Divide(&world->velocity_components[position], scl);
  }
}

// Change direction of entity toward vector
void Physics_ChangeDirection(World *world, Entity entity, Vector v) {
  int index = ECS_GetEntityPosition(entity);

  if (ECS_HasComponent(world, entity, C_VELOCITY)) {
    Vector position = world->position_components[index];
    world->velocity_components[index] = Vector_Subtract(&v, &position);
  }
}
