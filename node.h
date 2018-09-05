/* node.c: Huffman Node */

#pragma once

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/* Node Constants */

#define NODE_NOT_SYMBOL (-1)

/* Node Unions */

typedef union {
    char    string[sizeof(int64_t)];
    int64_t letter;
} Symbol;

/* Node Structures */

typedef struct node Node;

struct node {
    Symbol  symbol;
    size_t  count;
    Node   *left;
    Node   *right;
};

/* Node Functions */

typedef void (*NodeFunc)(const Node *n, char *encoding, void *arg);

Node *  node_create(int64_t symbol, size_t count, Node *left, Node *right);
Node *  node_delete(Node *n);

void    node_dump(const Node *n, FILE *stream);

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
