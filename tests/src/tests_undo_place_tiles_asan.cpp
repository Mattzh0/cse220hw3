#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "gtest/gtest.h"
#include "tests_aux.h"

class undo_place_tiles_asan_TestSuite : public testing::Test { 
    void SetUp() override {
        mkdir("./tests/actual_outputs/", 0700);
    }
};

TEST_F(undo_place_tiles_asan_TestSuite, undo01_asan) {
    expect_no_asan_errors(run_using_asan("undo01_asan"));
}

TEST_F(undo_place_tiles_asan_TestSuite, undo02_asan) {
    expect_no_asan_errors(run_using_asan("undo02_asan"));
}

TEST_F(undo_place_tiles_asan_TestSuite, undo03_asan) {
    expect_no_asan_errors(run_using_asan("undo03_asan"));
}

TEST_F(undo_place_tiles_asan_TestSuite, undo04_asan) {
    expect_no_asan_errors(run_using_asan("undo04_asan"));
}

TEST_F(undo_place_tiles_asan_TestSuite, undo05_asan) {
    expect_no_asan_errors(run_using_asan("undo05_asan"));
}

TEST_F(undo_place_tiles_asan_TestSuite, undo06_asan) {
    expect_no_asan_errors(run_using_asan("undo06_asan"));
}