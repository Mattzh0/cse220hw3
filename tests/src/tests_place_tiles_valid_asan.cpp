#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "gtest/gtest.h"
#include "tests_aux.h"

class place_tiles_valid_asan_TestSuite : public testing::Test { 
    void SetUp() override {
        mkdir("./tests/actual_outputs/", 0700);
    }
};

TEST_F(place_tiles_valid_asan_TestSuite, place_one_tile01_asan) {
    expect_no_asan_errors(run_using_asan("place_one_tile01_asan"));
}

TEST_F(place_tiles_valid_asan_TestSuite, place_horizontal_word07_asan) {
    expect_no_asan_errors(run_using_asan("place_horizontal_word07_asan"));
}

TEST_F(place_tiles_valid_asan_TestSuite, initialize_big_board_asan) {
    expect_no_asan_errors(run_using_asan("initialize_big_board_asan"));
}