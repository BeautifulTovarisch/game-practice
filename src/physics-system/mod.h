#ifndef PHYSICS_SYSTEM_H
#define PHYSICS_SYSTEM_H

#include <stdio.h>

#include "../ecs/components.h"
#include "../ecs/mod.h"

#include "../util/vector/mod.h"

void Physics_ChangeVelocity(World *world, Entity entity, Vector v);

#endif
