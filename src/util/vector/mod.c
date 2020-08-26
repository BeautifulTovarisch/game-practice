#include "mod.h"

Vector Vector_Add(Vector *v1, Vector *v2) {
  return (Vector){.x = v1->x + v2->x, .y = v1->y + v2->y};
}

Vector Vector_Subtract(Vector *v1, Vector *v2) {
  return (Vector){.x = v1->x - v2->x, .y = v1->y - v2->y};
}

Vector Vector_Divide(Vector *v, float scalar) {
  float divisor = scalar > 0 ? scalar : 1.0;
  return (Vector){.x = v->x / divisor, .y = v->y / divisor};
}

Vector Vector_Multiply(Vector *v, float scalar) {
  return (Vector){.x = v->x * scalar, .y = v->y * scalar};
}

float Vector_Magnitude(Vector *v) { return sqrt(v->x * v->x + v->y * v->y); }

void Vector_Normalize(Vector *v) {
  float mag = Vector_Magnitude(v);
  if (mag > 0) {
    *v = Vector_Multiply(v, 1 / mag);
  }
}
