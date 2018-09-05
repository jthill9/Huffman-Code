/* test_tree.c: Test Huffman Tree */

#include "debug.h"
#include "tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

/* Test Structures */

typedef struct {
    int64_t letter;
    char   *encoding;
} TestCase;

/* Test Functions */

int test_tree_create() {
    Tree *t = tree_create();
    assert(t);
    assert(t->root == NULL);
    for (size_t i = 0; i < TREE_COUNTS_SIZE; i++) {
        assert(t->counts[i] == 0);
    }
    return EXIT_SUCCESS;
}

int test_tree_delete() {
    Tree *t = tree_create();
    assert(t);

    t = tree_delete(t);
    assert(t == NULL);
    return EXIT_SUCCESS;
}

int test_tree_build_0() {
    Tree *t = tree_create();
    assert(t);

    char  tmpfile[BUFSIZ] = "test_tree.XXXXXXX";
    FILE *stream = fdopen(mkstemp(tmpfile), "r+");
    if (!stream) {
        return EXIT_FAILURE;
    }
    unlink(tmpfile);

    fputs("ABBCCC", stream);
    fseek(stream, 0, SEEK_SET);

    if (!tree_build(t, stream)) {
        return EXIT_FAILURE;
    }

    assert(t->counts['A'] == 1);
    assert(t->counts['B'] == 2);
    assert(t->counts['C'] == 3);

    t = tree_delete(t);
    assert(t == NULL);
    return EXIT_SUCCESS;
}

int test_tree_build_1() {
    Tree *t = tree_create();
    assert(t);

    char  tmpfile[BUFSIZ] = "test_tree.XXXXXXX";
    FILE *stream = fdopen(mkstemp(tmpfile), "r+");
    if (!stream) {
        return EXIT_FAILURE;
    }
    unlink(tmpfile);

    fputs("ABBCCC", stream);
    fseek(stream, 0, SEEK_SET);

    if (!tree_build(t, stream)) {
        return EXIT_FAILURE;
    }

    assert(t->counts['A'] == 1);
    assert(t->counts['B'] == 2);
    assert(t->counts['C'] == 3);
    
    assert(t->root);
    assert((char)t->root->symbol.letter == NODE_NOT_SYMBOL);
    assert(t->root->count == 6);
    assert(t->root->left);
    assert(t->root->right);

    t = tree_delete(t);
    assert(t == NULL);
    return EXIT_SUCCESS;
}

void test_node_count_nodes(const Node *n, char *encoding, void *arg) {
    int *count = (int *)arg;
    assert(n);
    assert(encoding);
    assert(strlen(encoding) > 0);
    
    (*count)++;
}

void test_node_check_cases(const Node *n, char *encoding, void *arg) {
    TestCase *cases = (TestCase *)arg;

    printf("%s = %s\n", n->symbol.string, encoding);
    for (TestCase *c = cases; c->letter; c++) {
        if ((char)n->symbol.letter == c->letter && strcmp(encoding, c->encoding) == 0)
            return;
    }
    assert(false);
}

void test_node_count_occurrences(const Node *n, char *encoding, void *arg) {
    int *count = (int *)arg;
    assert(n);
    assert(encoding);
    assert(strlen(encoding) > 0);
    
    *count += n->count;
}

int test_tree_walk_0() {
    Tree *t = tree_create();
    assert(t);

    char  tmpfile[BUFSIZ] = "test_tree.XXXXXXX";
    FILE *stream = fdopen(mkstemp(tmpfile), "r+");
    if (!stream) {
        return EXIT_FAILURE;
    }
    unlink(tmpfile);

    fputs("A", stream);
    fseek(stream, 0, SEEK_SET);

    if (!tree_build(t, stream)) {
        return EXIT_FAILURE;
    }
    
    assert(t->root);

    int count_nodes = 0;
    tree_walk(t, test_node_count_nodes, &count_nodes);
    assert(count_nodes == 1)
    
    int count_occurrences = 0;
    tree_walk(t, test_node_count_occurrences, &count_occurrences);
    assert(count_occurrences == 1)

    TestCase cases[] = {
        {'A', "0"},
        { 0 ,  0 },
    };
    tree_walk(t, test_node_check_cases, cases);

    t = tree_delete(t);
    assert(t == NULL);
    return EXIT_SUCCESS;
}

int test_tree_walk_1() {
    Tree *t = tree_create();
    assert(t);

    char  tmpfile[BUFSIZ] = "test_tree.XXXXXXX";
    FILE *stream = fdopen(mkstemp(tmpfile), "r+");
    if (!stream) {
        return EXIT_FAILURE;
    }
    unlink(tmpfile);

    fputs("AA", stream);
    fseek(stream, 0, SEEK_SET);

    if (!tree_build(t, stream)) {
        return EXIT_FAILURE;
    }
    
    assert(t->root);

    int count_nodes = 0;
    tree_walk(t, test_node_count_nodes, &count_nodes);
    assert(count_nodes == 1)
    
    int count_occurrences = 0;
    tree_walk(t, test_node_count_occurrences, &count_occurrences);
    assert(count_occurrences == 2)
    
    TestCase cases[] = {
        {'A', "0"},
        { 0 ,  0 },
    };
    tree_walk(t, test_node_check_cases, cases);

    t = tree_delete(t);
    assert(t == NULL);
    return EXIT_SUCCESS;
}

int test_tree_walk_2() {
    Tree *t = tree_create();
    assert(t);

    char  tmpfile[BUFSIZ] = "test_tree.XXXXXXX";
    FILE *stream = fdopen(mkstemp(tmpfile), "r+");
    if (!stream) {
        return EXIT_FAILURE;
    }
    unlink(tmpfile);

    fputs("AB", stream);
    fseek(stream, 0, SEEK_SET);

    if (!tree_build(t, stream)) {
        return EXIT_FAILURE;
    }
    
    assert(t->root);

    int count_nodes = 0;
    tree_walk(t, test_node_count_nodes, &count_nodes);
    assert(count_nodes == 2)
    
    int count_occurrences = 0;
    tree_walk(t, test_node_count_occurrences, &count_occurrences);
    assert(count_occurrences == 2)
    
    TestCase cases[] = {
        {'A', "0"},
        {'B', "1"},
        { 0 ,  0 },
    };
    tree_walk(t, test_node_check_cases, cases);

    t = tree_delete(t);
    assert(t == NULL);
    return EXIT_SUCCESS;
}

int test_tree_walk_3() {
    Tree *t = tree_create();
    assert(t);

    char  tmpfile[BUFSIZ] = "test_tree.XXXXXXX";
    FILE *stream = fdopen(mkstemp(tmpfile), "r+");
    if (!stream) {
        return EXIT_FAILURE;
    }
    unlink(tmpfile);

    fputs("ABBCCC", stream);
    fseek(stream, 0, SEEK_SET);

    if (!tree_build(t, stream)) {
        return EXIT_FAILURE;
    }
    
    assert(t->root);

    int count_nodes = 0;
    tree_walk(t, test_node_count_nodes, &count_nodes);
    assert(count_nodes == 3)
    
    int count_occurrences = 0;
    tree_walk(t, test_node_count_occurrences, &count_occurrences);
    assert(count_occurrences == 6)
    
    TestCase cases[] = {
        {'A', "10"},
        {'B', "11"},
        {'C', "0"},
        { 0 ,  0 },
    };
    tree_walk(t, test_node_check_cases, cases);

    t = tree_delete(t);
    assert(t == NULL);
    return EXIT_SUCCESS;
}

int test_tree_walk_4() {
    Tree *t = tree_create();
    assert(t);

    char  tmpfile[BUFSIZ] = "test_tree.XXXXXXX";
    FILE *stream = fdopen(mkstemp(tmpfile), "r+");
    if (!stream) {
        return EXIT_FAILURE;
    }
    unlink(tmpfile);

    fputs("abbcccddddeeeeeffffff", stream);
    fseek(stream, 0, SEEK_SET);

    if (!tree_build(t, stream)) {
        return EXIT_FAILURE;
    }
    
    assert(t->root);

    int count_nodes = 0;
    tree_walk(t, test_node_count_nodes, &count_nodes);
    assert(count_nodes == 6)
    
    int count_occurrences = 0;
    tree_walk(t, test_node_count_occurrences, &count_occurrences);
    assert(count_occurrences == 21)
    
    TestCase cases[] = {
        {'a', "1010"},
        {'b', "1011"},
        {'c', "100"},
        {'d', "00"},
        {'e', "01"},
        {'f', "11"},
        { 0 ,  0 },
    };
    tree_walk(t, test_node_check_cases, cases);

    t = tree_delete(t);
    assert(t == NULL);
    return EXIT_SUCCESS;
}

int test_tree_walk_5() {
    Tree *t = tree_create();
    assert(t);

    char  tmpfile[BUFSIZ] = "test_tree.XXXXXXX";
    FILE *stream = fdopen(mkstemp(tmpfile), "r+");
    if (!stream) {
        return EXIT_FAILURE;
    }
    unlink(tmpfile);

    fputs("i think that we've got what it takes to get this heart to start beating again so take it all the way", stream);
    fseek(stream, 0, SEEK_SET);

    if (!tree_build(t, stream)) {
        return EXIT_FAILURE;
    }
    
    assert(t->root);

    int count_nodes = 0;
    tree_walk(t, test_node_count_nodes, &count_nodes);
    assert(count_nodes == 18)
    
    int count_occurrences = 0;
    tree_walk(t, test_node_count_occurrences, &count_occurrences);
    assert(count_occurrences == 100)
    
    TestCase cases[] = {
        {'o' , "0000"},
        {'\'', "000100"},
        {'b' , "000101"},
        {'v' , "000110"},
        {'y' , "000111"},
        {'a' , "001"},
        {' ' , "01"},
        {'k' , "10000"},
        {'n' , "10001"},
        {'h' , "1001"},
        {'w' , "10100"},
        {'s' , "10101"},
        {'i' , "1011"},
        {'e' , "1100"},
        {'r' , "110100"},
        {'l' , "110101"},
        {'g' , "11011"},
        {'t' , "111"},
        { 0  ,  0 },
    };
    tree_walk(t, test_node_check_cases, cases);

    t = tree_delete(t);
    assert(t == NULL);
    return EXIT_SUCCESS;
}

int test_tree_walk_6() {
    Tree *t = tree_create();
    assert(t);

    char  tmpfile[BUFSIZ] = "test_tree.XXXXXXX";
    FILE *stream = fdopen(mkstemp(tmpfile), "r+");
    if (!stream) {
        return EXIT_FAILURE;
    }
    unlink(tmpfile);

    fputs("From now on"
          "These eyes will not be blinded by the lights"
          "From now on"
          "What's waited till tomorrow starts tonight"
          "Tonight"
          "Let this promise in me start"
          "Like an anthem in my heart"
          "From now on"
          "From now on", stream);
    fseek(stream, 0, SEEK_SET);

    if (!tree_build(t, stream)) {
        return EXIT_FAILURE;
    }
    
    assert(t->root);

    int count_nodes = 0;
    tree_walk(t, test_node_count_nodes, &count_nodes);
    assert(count_nodes == 24)
    
    int count_occurrences = 0;
    tree_walk(t, test_node_count_occurrences, &count_occurrences);
    assert(count_occurrences == 191)

    t = tree_delete(t);
    assert(t == NULL);
    return EXIT_SUCCESS;
}

/* Main Execution */

int main(int argc, char *argv[]) {
    if (argc != 2) {
    	fprintf(stderr, "Usage: %s NUMBER\n\n", argv[0]);
    	fprintf(stderr, "Where NUMBER is right of the following:\n");
    	fprintf(stderr, "    0. Test tree_create\n");
    	fprintf(stderr, "    1. Test tree_delete\n");
    	fprintf(stderr, "    2. Test tree_build_0\n");
    	fprintf(stderr, "    3. Test tree_build_1\n");
    	fprintf(stderr, "    4. Test tree_walk_0\n");
    	fprintf(stderr, "    5. Test tree_walk_1\n");
    	fprintf(stderr, "    6. Test tree_walk_2\n");
    	fprintf(stderr, "    7. Test tree_walk_3\n");
    	fprintf(stderr, "    8. Test tree_walk_4\n");
    	fprintf(stderr, "    9. Test tree_walk_5\n");
    	fprintf(stderr, "   10. Test tree_walk_6\n");
    	return EXIT_FAILURE;
    }

    int number = atoi(argv[1]);
    int status = EXIT_FAILURE;
    switch (number) {
	case  0: status = test_tree_create(); break;
	case  1: status = test_tree_delete(); break;
	case  2: status = test_tree_build_0(); break;
	case  3: status = test_tree_build_1(); break;
	case  4: status = test_tree_walk_0(); break;
	case  5: status = test_tree_walk_1(); break;
	case  6: status = test_tree_walk_2(); break;
	case  7: status = test_tree_walk_3(); break;
	case  8: status = test_tree_walk_4(); break;
	case  9: status = test_tree_walk_5(); break;
	case 10: status = test_tree_walk_6(); break;
	default:
	    fprintf(stderr, "Unknown NUMBER: %d\n", number);
	    break;
    }

    return status;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
