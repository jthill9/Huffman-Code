/* tree.h: Huffman Tree */

#pragma once

#include "node.h"

#include <stdbool.h>

/* Huffman Tree Constants */

#define TREE_COUNTS_SIZE (1<<8)

/* Huffman Tree Structures */

typedef struct {
    Node   *root;
    int64_t counts[TREE_COUNTS_SIZE];
} Tree;

/* Huffman Tree Functions */

Tree *  tree_create();
Tree *  tree_delete(Tree *t);

bool	tree_build(Tree *t, FILE *stream);
void    tree_walk(const Tree *t, NodeFunc f, void *arg);

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
