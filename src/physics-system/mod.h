#ifndef PHYSICS_SYSTEM_H
#define PHYSICS_SYSTEM_H

#include <stdio.h>

#include "../ecs/components.h"
#include "../ecs/mod.h"

#include "../util/vector/mod.h"

int Physics_EntityCollision(Entity e_a, Entity e_b);
int Physics_VectorCollision(Entity entity, Vector v);

void Physics_Accelerate(Entity entity, Vector v);
void Physics_UpdatePosition();
void Physics_ChangeDirection(Entity entity, Vector v);

#endif
