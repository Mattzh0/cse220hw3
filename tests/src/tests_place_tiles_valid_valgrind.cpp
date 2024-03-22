#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "gtest/gtest.h"
#include "tests_aux.h"

class place_tiles_valid_valgrind_TestSuite : public testing::Test { 
    void SetUp() override {
        mkdir("./tests/actual_outputs/", 0700);
    }
};

TEST_F(place_tiles_valid_valgrind_TestSuite, place_one_tile01_valgrind) {
    expect_no_valgrind_errors(run_using_valgrind("place_one_tile01_valgrind"));
}

TEST_F(place_tiles_valid_valgrind_TestSuite, place_horizontal_word07_valgrind) {
    expect_no_valgrind_errors(run_using_valgrind("place_horizontal_word07_valgrind"));
}

TEST_F(place_tiles_valid_valgrind_TestSuite, initialize_big_board_valgrind) {
    expect_no_valgrind_errors(run_using_valgrind("initialize_big_board_valgrind"));
}