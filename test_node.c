/* test_node.c: Test Huffman Node */

#include "debug.h"
#include "node.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Test Functions */

int test_node_create() {
    Node *p = NULL;

    for (int i = ' '; i <= '~'; i++) {
        Node *n = node_create(i, i, p, p);
        assert(n);
        assert(n->symbol.letter = i);
        if (i != '\\' || i != '"') {
            assert(n->symbol.string[0] == i);
        }
        assert(n->count == i);
        assert(n->left  == p);
        assert(n->right == p);
    }

    p = node_create('\"', 0, NULL, NULL);
    assert(!strcmp(p->symbol.string, "\\\""));

    p = node_create('\\', 0, NULL, NULL);
    assert(!strcmp(p->symbol.string, "\\\\"));
    
    p = node_create('\b', 0, NULL, NULL);
    assert(!strcmp(p->symbol.string, "\\b"));
    
    p = node_create('\f', 0, NULL, NULL);
    assert(!strcmp(p->symbol.string, "\\f"));

    p = node_create('\n', 0, NULL, NULL);
    assert(!strcmp(p->symbol.string, "\\n"));
    
    p = node_create('\r', 0, NULL, NULL);
    assert(!strcmp(p->symbol.string, "\\r"));
    
    p = node_create('\t', 0, NULL, NULL);
    assert(!strcmp(p->symbol.string, "\\t"));

    return EXIT_SUCCESS;
}

int test_node_delete() {
    Node *p = NULL;

    for (int i = ' '; i <= '~'; i++) {
        Node *n = node_create(i, i, p, p);
        assert(n);
        n = node_delete(n);
        assert(n == NULL);
    }
    
    return EXIT_SUCCESS;
}

int test_node_dump() {
    Node *n = node_create('C', 0, NULL, NULL);
    assert(n);
    node_dump(n, stdout);
    n = node_delete(n);
    assert(n == NULL);
    
    n = node_create('A', 1, NULL, NULL);
    assert(n);
    node_dump(n, stdout);
    n = node_delete(n);
    assert(n == NULL);
    
    n = node_create('L', 2, NULL, NULL);
    assert(n);
    node_dump(n, stdout);
    n = node_delete(n);
    assert(n == NULL);
    
    n = node_create('E', 3, NULL, NULL);
    assert(n);
    node_dump(n, stdout);
    n = node_delete(n);
    assert(n == NULL);
    
    n = node_create('B', 4, NULL, NULL);
    assert(n);
    node_dump(n, stdout);
    n = node_delete(n);
    
    n = node_create('\n', 5, NULL, NULL);
    assert(n);
    node_dump(n, stdout);
    n = node_delete(n);
    assert(n == NULL);
    return EXIT_SUCCESS;
}

/* Main Execution */

int main(int argc, char *argv[]) {
    if (argc != 2) {
    	fprintf(stderr, "Usage: %s NUMBER\n\n", argv[0]);
    	fprintf(stderr, "Where NUMBER is right of the following:\n");
    	fprintf(stderr, "    0. Test node_create\n");
    	fprintf(stderr, "    1. Test node_delete\n");
    	fprintf(stderr, "    2. Test node_dump\n");
    	return EXIT_FAILURE;
    }

    int number = atoi(argv[1]);
    int status = EXIT_FAILURE;
    switch (number) {
	case 0:	status = test_node_create(); break;
	case 1:	status = test_node_delete(); break;
	case 2:	status = test_node_dump(); break;
	default:
	    fprintf(stderr, "Unknown NUMBER: %d\n", number);
	    break;
    }

    return status;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
