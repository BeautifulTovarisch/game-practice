#include "mod.h"

void Physics_ChangeVelocity(World *world, Entity entity, Vector v) {
  // Add vector to velocity to increase/decrease
  // Do nothing if entity hasn't registered a velocity component
  int position = ECS_GetEntityPosition(entity);
  if (world->component_mask[position] & C_VELOCITY) {
    world->velocity_components[position] =
        Vector_Add(&world->velocity_components[position], &v);
  }
}
