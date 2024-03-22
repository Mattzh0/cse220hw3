#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "gtest/gtest.h"
#include "tests_aux.h"

class undo_place_tiles_valgrind_TestSuite : public testing::Test { 
    void SetUp() override {
        mkdir("./tests/actual_outputs/", 0700);
    }
};

TEST_F(undo_place_tiles_valgrind_TestSuite, undo01_valgrind) {
    expect_no_valgrind_errors(run_using_valgrind("undo01_valgrind"));
}

TEST_F(undo_place_tiles_valgrind_TestSuite, undo02_valgrind) {
    expect_no_valgrind_errors(run_using_valgrind("undo02_valgrind"));
}

TEST_F(undo_place_tiles_valgrind_TestSuite, undo03_valgrind) {
    expect_no_valgrind_errors(run_using_valgrind("undo03_valgrind"));
}

TEST_F(undo_place_tiles_valgrind_TestSuite, undo04_valgrind) {
    expect_no_valgrind_errors(run_using_valgrind("undo04_valgrind"));
}

TEST_F(undo_place_tiles_valgrind_TestSuite, undo05_valgrind) {
    expect_no_valgrind_errors(run_using_valgrind("undo05_valgrind"));
}

TEST_F(undo_place_tiles_valgrind_TestSuite, undo06_valgrind) {
    expect_no_valgrind_errors(run_using_valgrind("undo06_valgrind"));
}