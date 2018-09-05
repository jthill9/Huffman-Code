/* queue.c: Priority Queue (Min Heap) */

#include "debug.h"
#include "queue.h"

/* Internal Priority Queue Prototypes */

bool    queue_resize(Queue *q, size_t capacity);
void    queue_bubble_up(Queue *q, size_t i);
void    queue_bubble_down(Queue *q, size_t i);
size_t  queue_minimum_child(Queue *q, size_t i);

/* External Priority Queue Functions */

/**
 * Create Queue structure.
 * @param   capacity        Initial capacity.
 * @return  Newly allocated Queue structure with specified capacity.
 */
Queue * queue_create(size_t capacity) {
    if (capacity == 0) capacity = PRIORITY_QUEUE_CAPACITY;
    Queue *q = calloc(1, sizeof(Queue));
    if (q) {
        q->capacity = capacity;
        q->nodes = calloc(capacity, sizeof(Node*));
        if (q->nodes == NULL) {
            free(q);
            return NULL;
        }
    }
    return q;
}

/**
 * Delete Queue structure.
 * @param   q           Queue structure.
 * @return  NULL.
 */
Queue * queue_delete(Queue *q) {
    if (q) {
        free(q->nodes);
        free(q);
    }
    return NULL;
}

/**
 * Push Node into Queue structure.
 * @param   q           Queue structure.
 * @param   n           Node structure.
 * @return  Whether or not the operation was successful.
 */
bool    queue_push(Queue *q, Node *n) {
    if (q->size >= q->capacity) {
        if(!queue_resize(q, q->capacity * 2)) return false;
    }
    q->nodes[q->size] = n;
    queue_bubble_up(q, q->size);
    q->size = q->size + 1;
    return true;
}

/**
 * Pop minimum Node into Queue structure.
 * @param   q           Queue structure.
 * @return  Minimum Node structure (by count) or NULL.
 */
Node *	queue_pop(Queue *q) {
    if (q->size == 0) return NULL;
    Node* n = q->nodes[0];
    q->size = q->size - 1;
    q->nodes[0] = q->nodes[q->size];
    queue_bubble_down(q, 0);
    return n;
}

/**
 * Dump Queue structure.
 * @param   q           Queue structure.
 * @param   stream      I/O stream to write to.
 */
void    queue_dump(const Queue *q, FILE *stream) {
    for (size_t i = 0; i < q->size; i++) {
        node_dump(q->nodes[i], stream);
    }
}

/* Internal Priority Queue Functions */

/**
 * Resize Queue structure.
 * @param   q           Queue structure.
 * @param   capacity    New capacity.
 * @return  Whether or not operation succeeded.
 */
bool    queue_resize(Queue *q, size_t capacity) {
    q->nodes = realloc(q->nodes, sizeof(Node *) * capacity);
    q->capacity = capacity;
    return q->nodes;
}

/**
 * Bubble up Node in Queue structure.
 * @param   q           Queue structure.
 * @param   i           Index to current Node structure.
 */
void    queue_bubble_up(Queue *q, size_t i) {
    while(i > 0) {
        if (q->nodes[i]->count < q->nodes[PARENT(i)]->count) {
            Node *temp = q->nodes[PARENT(i)];
            q->nodes[PARENT(i)] = q->nodes[i];
            q->nodes[i] = temp;
        }
    i = PARENT(i);
    }
}

/**
 * Bubble down Node in Queue structure.
 * @param   q           Queue structure.
 * @param   i           Index to current Node structure.
 */
void    queue_bubble_down(Queue *q, size_t i) {
    while (LEFT_CHILD(i) < q->size) {
        size_t min_child = queue_minimum_child(q, i);
        if (q->nodes[i]->count > q->nodes[queue_minimum_child(q, i)]->count) {
            Node *temp = q->nodes[queue_minimum_child(q, i)];
            q->nodes[queue_minimum_child(q, i)] = q->nodes[i];
            q->nodes[i] = temp;
        }
        i = min_child;
    }
}

/**
 * Determines index of child with minimum value.
 * @param   q           Queue structure.
 * @param   i           Index to current Node structure.
 */
size_t  queue_minimum_child(Queue *q, size_t i) {
    if (q) {
        if (q->nodes[LEFT_CHILD(i)]->count < q->nodes[RIGHT_CHILD(i)]->count) return LEFT_CHILD(i);
        return RIGHT_CHILD(i);
    }
    return 0;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
