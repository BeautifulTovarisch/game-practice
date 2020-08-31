#include "mod.h"

/* Detect collisions by separating axis theorem.
 * Only need to write 'half' the axis test as parameter
 * order is swapped in order to accommodate.
 */
static int separating_x(Collision a, Collision b) { return a.max.x < b.min.x; }
static int separating_y(Collision a, Collision b) { return a.max.y < b.min.y; }

int Physics_EntityCollision(Entity e_a, Entity e_b) {
  // Get collision boxes
  Collision coll_a = ECS_GetComponent(e_a, C_COLLISION)->component.collision,
            coll_b = ECS_GetComponent(e_a, C_COLLISION)->component.collision;

  // If separating axes are found in either direction
  if (separating_x(coll_a, coll_b) || separating_x(coll_b, coll_a)) {
    return 0;
  }
  if (separating_y(coll_a, coll_b) || separating_y(coll_b, coll_a)) {
    return 0;
  }

  return 1;
}

// Determine if collision lies inside collision box
// e.g mouse inside button
int Physics_VectorCollision(Entity entity, Vector v) {
  if (!ECS_HasComponent(entity, C_COLLISION)) {
    return 0;
  }

  Collision col = ECS_GetComponent(entity, C_COLLISION)->component.collision;

  return v.x >= col.min.x && v.y >= col.min.y && v.x <= (col.max.x) &&
         v.y <= (col.max.y);
}

// Update position of entities with Position and Velocity vectors
void Physics_UpdatePosition() {
  for (int entity = 1; entity <= ECS_GetEntityCount(); entity++) {
    if (ECS_HasComponent(entity, (C_POSITION | C_VELOCITY | C_ACCELERATION))) {
      Vector *velocity =
          &ECS_GetComponent(entity, C_VELOCITY)->component.vector;
      Vector *position =
          &ECS_GetComponent(entity, C_POSITION)->component.vector;
      Vector *acceleration =
          &ECS_GetComponent(entity, C_ACCELERATION)->component.vector;

      *velocity = Vector_Add(velocity, acceleration);
      *position = Vector_Add(position, velocity);
    }
  }
}

void Physics_Accelerate(Entity entity, Vector v) {
  if (ECS_HasComponent(entity, C_POSITION | C_ACCELERATION)) {
    Vector *acceleration =
        &ECS_GetComponent(entity, C_ACCELERATION)->component.vector;
    *acceleration = Vector_Add(acceleration, &v);
  }
}

void Physics_ApplyFriction(Entity entity, float scalar) {
  if (ECS_HasComponent(entity, C_ACCELERATION)) {
    Vector *acceleration =
        &ECS_GetComponent(entity, C_ACCELERATION)->component.vector;
    *acceleration = Vector_Multiply(acceleration, 0.99);
  }
}

// Change direction of entity toward collision
void Physics_ChangeDirection(Entity entity, Vector v) {
  if (ECS_HasComponent(entity, C_VELOCITY)) {
    Vector *velocity = &ECS_GetComponent(entity, C_VELOCITY)->component.vector;
    *velocity = Vector_Subtract(&v, velocity);
  }
}
