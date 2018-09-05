/* node.c: Huffman Node */

#include "node.h"
#include <string.h>

/* Internal Node Functions */

void    node_set_symbol(Node *n, int64_t letter);

/* External Node Functions */

/**
 * Create Node structure.
 * @param   symbol      Symbol letter.
 * @param   count       Initial count.
 * @param   left        Left Node child.
 * @param   right       Right Node child.
 * @return  Newly allocated Node structure with specified attributes.
 */
Node *  node_create(int64_t symbol, size_t count, Node *left, Node *right) {
    Node *n = malloc(sizeof(Node));
    if (n) {
        node_set_symbol(n, symbol);
        n->count = count;
        n->left = left;
        n->right = right;
        return n;
    }
    return NULL;
}

/**
 * Delete Node structure.
 * @param   n           Node structure.
 * @return  NULL.
 */
Node *  node_delete(Node *n) {
    if (n) {
        node_delete(n->right);
        node_delete(n->left);
        free(n);
    }
    return NULL;
}

/**
 * Dump Node structure.
 * @param   n           Node structure.
 * @param   stream      I/O to write to.
 */
void    node_dump(const Node *n, FILE *stream) {
    fprintf(stream, "Node{symbol: %s, count: %zu, left: 0x%ld, right: 0x%ld}\n", n->symbol.string, n->count, (int64_t)(n->left), (int64_t)(n->right));
}

/* Internal Node Functions */

/**
 * Set symbol attribute of Node structure.
 * @param   n           Node structure.
 * @param   letter      Node symbol letter value.
 */
void    node_set_symbol(Node *n, int64_t letter) {
    n->symbol.letter = letter;
    switch(letter) {
        case '\"':
            strcpy(n->symbol.string, "\\\"");
            break;
        case '\\':
            strcpy(n->symbol.string, "\\\\");
            break;
        case '\b':
            strcpy(n->symbol.string, "\\b");
            break;
        case '\f':
            strcpy(n->symbol.string, "\\f");
            break;
        case '\n':
            strcpy(n->symbol.string, "\\n");
            break;
        case '\r':
            strcpy(n->symbol.string, "\\r");
            break;
        case '\t':
            strcpy(n->symbol.string, "\\t");
            break;
    }
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
