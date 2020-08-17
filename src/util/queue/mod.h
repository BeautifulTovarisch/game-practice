#ifndef QUEUE_H
#define QUEUE_H

#include <limits.h>
#include <stdlib.h>

typedef struct Queue {
  int size;
  int back;
  int front;
  unsigned capacity;
  int *items;
} Queue;

static int is_full(Queue *queue);
static int is_empty(Queue *queue);

Queue *Queue_Create(unsigned capacity);

void Queue_Enqueue(Queue *queue, int data);
int Queue_Dequeue(Queue *queue);

#endif
