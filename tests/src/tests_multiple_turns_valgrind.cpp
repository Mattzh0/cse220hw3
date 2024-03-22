#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "gtest/gtest.h"
#include "tests_aux.h"

class multiple_turns_valgrind_TestSuite : public testing::Test { 
    void SetUp() override {
        mkdir("./tests/actual_outputs/", 0700);
    }
};

TEST_F(multiple_turns_valgrind_TestSuite, multiple01_valgrind) {
    expect_no_valgrind_errors(run_using_valgrind("multiple01_valgrind"));
}

TEST_F(multiple_turns_valgrind_TestSuite, multiple02_valgrind) {
    expect_no_valgrind_errors(run_using_valgrind("multiple02_valgrind"));
}

TEST_F(multiple_turns_valgrind_TestSuite, multiple03_valgrind) {
    expect_no_valgrind_errors(run_using_valgrind("multiple03_valgrind"));
}

TEST_F(multiple_turns_valgrind_TestSuite, multiple04_valgrind) {
    expect_no_valgrind_errors(run_using_valgrind("multiple04_valgrind"));
}

TEST_F(multiple_turns_valgrind_TestSuite, multiple05_valgrind) {
    expect_no_valgrind_errors(run_using_valgrind("multiple05_valgrind"));
}

TEST_F(multiple_turns_valgrind_TestSuite, multiple06_valgrind) {
    expect_no_valgrind_errors(run_using_valgrind("multiple06_valgrind"));
}