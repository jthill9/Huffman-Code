/* queue.h: Priority Queue (Min Heap) */

#pragma once

#include "node.h"

#include <stdbool.h>

/* Priority Queue Constants */

#define PRIORITY_QUEUE_CAPACITY (1<<8)

/* Priority Queue Macros */

#define PARENT(i)       ((i-1)/2)
#define LEFT_CHILD(i)   (2*(i) + 1)
#define RIGHT_CHILD(i)  (2*(i) + 2)

/* Priority Queue Structures */

typedef struct queue {
    Node   **nodes;         /* Array of Node pointers */
    size_t   size;          /* Number of Nodes in Queue */
    size_t   capacity;      /* Total number of slots allocated */
} Queue;

/* Priority Queue Functions */

Queue * queue_create(size_t capacity);
Queue * queue_delete(Queue *q);

bool    queue_push(Queue *q, Node *n);
Node  * queue_pop(Queue *q);

void    queue_dump(const Queue *q, FILE *stream);

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
