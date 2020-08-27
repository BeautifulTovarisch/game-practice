#ifndef PHYSICS_SYSTEM_H
#define PHYSICS_SYSTEM_H

#include <stdio.h>

#include "../ecs/components.h"
#include "../ecs/mod.h"

#include "../util/vector/mod.h"

int Physics_EntityCollision(World *world, Entity e_a, Entity e_b);
int Physics_VectorCollision(World *world, Entity entity, Vector v);

// TODO :: Determine actual physics terminology
void Physics_ReduceVelocity(World *world, Entity entity, float scl);
void Physics_ChangeDirection(World *world, Entity entity, Vector v);
void Physics_ChangeVelocity(World *world, Entity entity, Vector v);

#endif
