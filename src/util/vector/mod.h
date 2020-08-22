#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>

typedef struct Vector {
  float x;
  float y;
} Vector;

Vector Vector_Add(Vector v1, Vector v2) {
  return (Vector){.x = v1.x + v2.x, .y = v1.y + v2.y};
}

#endif
