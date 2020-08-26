#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>

typedef struct Vector {
  float x;
  float y;
} Vector;

Vector Vector_Add(Vector *v1, Vector *v2);
Vector Vector_Divide(Vector *v, float scalar);
Vector Vector_Multiply(Vector *v, float scalar);
Vector Vector_Subtract(Vector *v1, Vector *v2);

float Vector_Magnitude(Vector *v);

void Vector_Normalize(Vector *v);

#endif
