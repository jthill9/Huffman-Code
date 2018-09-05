/* test_queue.c: Test Priority Queue */

#include "debug.h"
#include "queue.h"

#include <stdio.h>
#include <stdlib.h>

/* Test Constants */

Node TestNodes[] = {
    {{.letter = 'A'}, 1, NULL, NULL},
    {{.letter = 'B'}, 4, NULL, NULL},
    {{.letter = 'C'}, 0, NULL, NULL},
    {{.letter = 'E'}, 3, NULL, NULL},
    {{.letter = 'L'}, 2, NULL, NULL},
    {{.letter =  0 }, 0, NULL, NULL},
};

#define TEST_CAPACITY   (4)

/* Test Functions */

int test_queue_create() {
    Queue *q = queue_create(0);
    assert(q);
    assert(q->size     == 0);
    assert(q->capacity == PRIORITY_QUEUE_CAPACITY);
    assert(q->nodes);

    q = queue_create(TEST_CAPACITY);
    assert(q);
    assert(q->size     == 0);
    assert(q->capacity == TEST_CAPACITY);
    assert(q->nodes);

    return EXIT_SUCCESS;
}

int test_queue_delete() {
    Queue *q = queue_create(TEST_CAPACITY);
    assert(q);

    q = queue_delete(q);
    assert(q == NULL);

    q = queue_create(0);
    assert(q);

    for (Node *n = TestNodes; n->symbol.letter; n++) {
        q->nodes[q->size++] = n;
    }
    q = queue_delete(q);
    assert(q == NULL);

    return EXIT_SUCCESS;
}

int test_queue_push_0() {
    Queue *q = queue_create(0);
    assert(q);

    for (Node *n = TestNodes; n->symbol.letter; n++) {
        assert(queue_push(q, n));
    }
    q = queue_delete(q);
    assert(q == NULL);
    return EXIT_SUCCESS;
}

int test_queue_push_1() {
    Queue *q = queue_create(TEST_CAPACITY);
    assert(q);

    for (Node *n = TestNodes; n->symbol.letter; n++) {
        assert(queue_push(q, n));
    }
    q = queue_delete(q);
    assert(q == NULL);
    return EXIT_SUCCESS;
}

int test_queue_push_2() {
    Queue *q = queue_create(TEST_CAPACITY);
    assert(q);

    for (Node *n = TestNodes; n->symbol.letter; n++) {
        assert(queue_push(q, n));
    }

    for (size_t i = 1; i < q->size; i++) {
        size_t p = PARENT(i);
        assert(q->nodes[i]->count > q->nodes[p]->count);
    }

    q = queue_delete(q);
    assert(q == NULL);
    return EXIT_SUCCESS;
}

int test_queue_pop() {
    Queue *q = queue_create(TEST_CAPACITY);
    assert(q);

    for (Node *n = TestNodes; n->symbol.letter; n++) {
        assert(queue_push(q, n));
    }

    size_t count = 0;
    while (q->size) {
        Node *n = queue_pop(q);
        assert(n->count == count);
        count++;
    }

    q = queue_delete(q);
    assert(q == NULL);
    return EXIT_SUCCESS;
}

int test_queue_dump() {
    Queue *q1 = queue_create(TEST_CAPACITY);
    assert(q1);
    Queue *q2 = queue_create(TEST_CAPACITY);
    assert(q2);

    for (Node *n = TestNodes; n->symbol.letter; n++) {
        assert(queue_push(q1, n));
    }
    queue_dump(q1, stdout);

    while (q1->size) {
        queue_push(q2, queue_pop(q1));
    }
    queue_dump(q2, stdout);

    q1 = queue_delete(q1);
    assert(q1 == NULL);
    q2 = queue_delete(q2);
    assert(q2 == NULL);
    return EXIT_SUCCESS;
}

/* Main Execution */

int main(int argc, char *argv[]) {
    if (argc != 2) {
    	fprintf(stderr, "Usage: %s NUMBER\n\n", argv[0]);
    	fprintf(stderr, "Where NUMBER is right of the following:\n");
    	fprintf(stderr, "    0. Test queue_create\n");
    	fprintf(stderr, "    1. Test queue_delete\n");
    	fprintf(stderr, "    2. Test queue_push 0\n");
    	fprintf(stderr, "    3. Test queue_push 1\n");
    	fprintf(stderr, "    4. Test queue_push 2\n");
    	fprintf(stderr, "    5. Test queue_pop\n");
    	fprintf(stderr, "    6. Test queue_dump\n");
    	return EXIT_FAILURE;
    }

    int number = atoi(argv[1]);
    int status = EXIT_FAILURE;
    switch (number) {
	case 0:	status = test_queue_create(); break;
	case 1:	status = test_queue_delete(); break;
	case 2:	status = test_queue_push_0(); break;
	case 3:	status = test_queue_push_1(); break;
	case 4:	status = test_queue_push_2(); break;
	case 5:	status = test_queue_pop(); break;
	case 6:	status = test_queue_dump(); break;
	default:
	    fprintf(stderr, "Unknown NUMBER: %d\n", number);
	    break;
    }

    return status;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
