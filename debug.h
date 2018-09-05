/* debug.h: Debugging Macros */

#pragma once

#include <stdio.h>
#include <stdlib.h>

#define debug(M, ...) \
    fprintf(stderr, "DEBUG %s:%d:%s: " M "\n", __FILE__, __LINE__, __func__, ##__VA_ARGS__)

#define assert(condition) \
    do { \
    	if (!(condition)) { \
	    fprintf(stderr, "ASSERT %s:%d:%s: " #condition "\n", __FILE__, __LINE__, __func__); \
	    exit(EXIT_FAILURE); \
	} \
    } while (0);

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
