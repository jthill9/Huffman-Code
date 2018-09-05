/* tree.c: Huffman Tree */

#include "queue.h"
#include "tree.h"
#include <stdio.h>
#include <string.h>

/* Internal Huffman Tree Prototyes */

void	tree_count(Tree *t, FILE *stream);
Queue *	tree_queue(Tree *t);
void	tree_walk_node(const Node *n, NodeFunc f, void *arg, char *encoding);

/* External Huffman Tree Functions */

/**
 * Create Tree structure.
 * @return  Newly allocated and initialized Tree structure.
 */
Tree *  tree_create() {
    Tree *t = calloc(1, sizeof(Tree));
    if (t) {
        t->root = NULL;
        return t;
    }
    return NULL;
}

/**
 * Delete Tree structure.
 * @param   t           Tree structure.
 * @return  NULL.
 */
Tree *  tree_delete(Tree *t) {
    if(t) {
        node_delete(t->root);
        free(t);
    }
    return NULL;
}

/**
 * Build internal Tree structure.
 * @param   t           Tree structure.
 * @param   stream      I/O stream to read from.
 * @return  Whether or not the operation succeeded.
 */
bool	tree_build(Tree *t, FILE *stream) {
    if (t) {
        tree_count(t, stream);
        Queue *q = tree_queue(t);
        if (!q) return false;
        while (q->size > 1) {
            Node *a = queue_pop(q);
            Node *b = queue_pop(q);
            Node *new_node = node_create(NODE_NOT_SYMBOL, a->count + b->count, a, b);
            queue_push(q, new_node);
        }
        t->root = queue_pop(q);
        queue_delete(q);
        return true;
    }
    return false;
}

/**
 * Walk Tree structure.
 * @param   t           Tree structure.
 * @param   f           Node function.
 * @param   arg         Node function argument.
 * @return  Whether or not the operation succeeded.
 */
void	tree_walk(const Tree *t, NodeFunc f, void *arg) {
    char encoding[BUFSIZ] = "";
    tree_walk_node(t->root, f, arg, encoding);
}

/* Internal Tree Functions */

/**
 * Build internal counts table in Tree structure.
 * @param   t           Tree structure.
 * @param   stream      I/O stream to read from.
 * @return
 */
void	tree_count(Tree *t, FILE *stream) {
    char buffer[BUFSIZ];

    while (fgets(buffer, BUFSIZ, stream)) {
        buffer[strlen(buffer)] = '\0';
        for (char *c = buffer; *c; c++) {
            t->counts[(int64_t)(*c)] = t->counts[(int64_t)(*c)] + 1;
        }
    }
}

/**
 * Create Priority Queue out of counts table in Tree structure.
 * @param   t           Tree structure.
 * @return  Priority Queue of Nodes corresponding to counts in Tree.
 */
Queue *	tree_queue(Tree *t) {
    Queue *q = queue_create(0);
    if (!q) return NULL;
    for (int i = 0; i < TREE_COUNTS_SIZE; i++) {
        if (!t->counts[i]) continue;
        Node *n = node_create(i, t->counts[i], NULL, NULL);
        if (!n) {
            queue_delete(q);
            return NULL;
        }
        if (!queue_push(q, n)) {
            queue_delete(q);
            return NULL;
        }
    }
    return q;
}

/**
 * Recursively walk Tree nodes.
 * @param   n           Node structure.
 * @param   f           Node function.
 * @param   arg         Node function argument.
 * @param   encoding    Node encoding.
 */
void	tree_walk_node(const Node *n, NodeFunc f, void *arg, char *encoding) {
    if (!n->left && !n->right) {
        if (strlen(encoding) == 0)
            strcat(encoding, "0");
        f(n, encoding, arg);
    }
    else {
        tree_walk_node(n->left, f, arg, strcat(encoding, "0"));
        encoding[strlen(encoding) - 1] = '\0';
        tree_walk_node(n->right, f, arg, strcat(encoding, "1"));
        encoding[strlen(encoding) - 1] = '\0';
    }
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
