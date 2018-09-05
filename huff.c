/* huff.c */

#include "tree.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Constants */

typedef enum {
    TSV,
    CSV,
    YAML,
    JSON,
} Format;

/* Globals */

char * PROGRAM_NAME = NULL;

/* Functions */

void usage(int status) {
    fprintf(stderr, "Usage: %s FILES...\n", PROGRAM_NAME);
    fprintf(stderr, "Flags:\n\n");
    fprintf(stderr, "    -f FORMAT    Output format (tsv, csv, yaml, json)\n");

    exit(status);
}

void dump_func(const Node *n, char *encoding, void *arg) {
    int *count = (int *)arg;
    switch (*count) {
        case TSV:
            printf("%s\t%s\t%zu\n", n->symbol.string, encoding, (n->count));
            break;
        case CSV:
            printf("\"%s\",\"%s\",%zu\n", n->symbol.string, encoding, (n->count));
            break;
        case YAML:
            printf("\"%s\": {\"encoding\": \"%s\", \"count\": %zu}\n", n->symbol.string, encoding, (n->count));
            break;
        case JSON:
            printf("  \"%s\": {\"encoding\": \"%s\", \"count\": %zu},\n", n->symbol.string, encoding, (n->count));
            break;
    }
}

void huff_stream(FILE *stream, int format) {
    Tree *t = tree_create();
    if (!tree_build(t, stream)) exit(1);
    if (format == JSON) printf("{\n");
    tree_walk(t, dump_func, &format);
    if (format == JSON) printf("}\n");
    tree_delete(t);
}

void huff_file(const char *path, int format) {
    FILE *fs = fopen(path, "r");
    if (fs == NULL) {
        fprintf(stderr, "%s: %s: %s\n", PROGRAM_NAME, path, strerror(errno));
        return;
    }
    huff_stream(fs, format);
    fclose(fs);                                                                   /* 7 */
}

/* Main Execution */

int main(int argc, char *argv[]) {
    /* Parse command line arguments */
    int argind = 1;
    int format = 0;
    char *tsv = "tsv";
    char *csv = "csv";
    char *yaml = "yaml";
    char *json = "json";

    while (argind < argc && strlen(argv[argind]) > 1 && argv[argind][0] == '-') { /* 8 */
        char *arg = argv[argind++];
        switch (arg[1]) {
            case 'f':
                if (strcmp(argv[argind], tsv) == 0) format = TSV;
                else if (strcmp(argv[argind], csv) == 0) format = CSV;
                else if (strcmp(argv[argind], yaml) == 0) format = YAML;
                else if (strcmp(argv[argind], json) ==0) format = JSON;
                else usage(1);
                argind++;
                break;
            case 'h':
                usage(0);
                break;
            default:
                usage(1);
                break;
        }
    }

    /* Process each file */
    if (argind == argc) {
        huff_stream(stdin, format);
    }
    else {
        while (argind < argc) {
            char *path = argv[argind++];
            if (strcmp(path, "-") == 0) {                                         /* 9 */
                huff_stream(stdin, format);
            } else {
                huff_file(path, format);
            }
        }
    }

    return EXIT_SUCCESS;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
