#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <assert.h>
#include "gtest/gtest.h"

#define INFO(...) fprintf(stderr, "[          ] [ INFO ] "); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n"); fflush(stderr)
#define ERROR(...) fprintf(stderr, "[          ] [ ERR  ] "); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n"); fflush(stderr)

char *load_file(const char *filename);
void expect_no_valgrind_errors(int status);
void expect_no_asan_errors(int status);
int run_using_valgrind(const char *test_name);
int run_using_asan(const char *test_name);