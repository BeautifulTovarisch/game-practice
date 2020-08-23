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

void Physics_ChangeVelocity(World *world, Entity entity, Vector v) {
  // Add vector to velocity to increase/decrease
  // Do nothing if entity hasn't registered a velocity component
  int position = ECS_GetEntityPosition(entity);
  if (world->component_mask[position] & C_VELOCITY) {
    world->velocity_components[position] =
        Vector_Add(&world->velocity_components[position], &v);
  }
}
