#include "mod.h"

Queue *Queue_Create(unsigned capacity) {
  Queue *queue = (Queue *)malloc(sizeof(Queue));

  queue->capacity = capacity;
  queue->size = 0;
  queue->front = 0;

  queue->back = capacity - 1;

  queue->items = (int *)malloc(queue->capacity * sizeof(int));

  return queue;
}

static int is_full(Queue *queue) { return queue->size == queue->capacity; }

static int is_empty(Queue *queue) { return queue->size == 0; }

void Queue_Enqueue(Queue *queue, int data) {
  if (is_full(queue)) {
    return;
  }

  queue->back = (queue->back + 1) % queue->capacity;
  queue->items[queue->back] = data;
  queue->size++;
}

int Queue_Dequeue(Queue *queue) {
  if (is_empty(queue)) {
    return INT_MIN;
  }

  int data = queue->items[queue->front];
  queue->front = (queue->front + 1) % queue->capacity;
  queue->size--;

  return data;
}
