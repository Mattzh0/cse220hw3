#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "gtest/gtest.h"
#include "tests_aux.h"

class place_tiles_invalid_asan_TestSuite : public testing::Test { 
    void SetUp() override {
        mkdir("./tests/actual_outputs/", 0700);
    }
};

TEST_F(place_tiles_invalid_asan_TestSuite, invalid_horiz_resize01_asan) {
    expect_no_asan_errors(run_using_asan("invalid_horiz_resize01_asan"));
}

TEST_F(place_tiles_invalid_asan_TestSuite, invalid_vert_overlap01_asan) {
    expect_no_asan_errors(run_using_asan("invalid_vert_overlap01_asan"));
}

TEST_F(place_tiles_invalid_asan_TestSuite, invalid_placement03_asan) {
    expect_no_asan_errors(run_using_asan("invalid_placement03_asan"));
}

TEST_F(place_tiles_invalid_asan_TestSuite, height_exceed_limit02_asan) {
    expect_no_asan_errors(run_using_asan("height_exceed_limit02_asan"));
}

TEST_F(place_tiles_invalid_asan_TestSuite, invalid_vert_touch04_asan) {
    expect_no_asan_errors(run_using_asan("invalid_vert_touch04_asan"));
}

TEST_F(place_tiles_invalid_asan_TestSuite, invalid_vert_touch08_asan) {
    expect_no_asan_errors(run_using_asan("invalid_vert_touch08_asan"));
}

TEST_F(place_tiles_invalid_asan_TestSuite, invalid_horiz_no_touch02_asan) {
    expect_no_asan_errors(run_using_asan("invalid_horiz_no_touch02_asan"));
}

