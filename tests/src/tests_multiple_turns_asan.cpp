#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "gtest/gtest.h"
#include "tests_aux.h"

class multiple_turns_asan_TestSuite : public testing::Test { 
    void SetUp() override {
        mkdir("./tests/actual_outputs/", 0700);
    }
};

TEST_F(multiple_turns_asan_TestSuite, multiple01_asan) {
    expect_no_asan_errors(run_using_asan("multiple01_asan"));
}

TEST_F(multiple_turns_asan_TestSuite, multiple02_asan) {
    expect_no_asan_errors(run_using_asan("multiple02_asan"));
}

TEST_F(multiple_turns_asan_TestSuite, multiple03_asan) {
    expect_no_asan_errors(run_using_asan("multiple03_asan"));
}

TEST_F(multiple_turns_asan_TestSuite, multiple04_asan) {
    expect_no_asan_errors(run_using_asan("multiple04_asan"));
}

TEST_F(multiple_turns_asan_TestSuite, multiple05_asan) {
    expect_no_asan_errors(run_using_asan("multiple05_asan"));
}

TEST_F(multiple_turns_asan_TestSuite, multiple06_asan) {
    expect_no_asan_errors(run_using_asan("multiple06_asan"));
}