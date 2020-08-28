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

Queue *Queue_Create(unsigned capacity);

int Queue_Dequeue(Queue *queue);

void Queue_Destroy(Queue **queue);
void Queue_Enqueue(Queue *queue, int data);

#endif
