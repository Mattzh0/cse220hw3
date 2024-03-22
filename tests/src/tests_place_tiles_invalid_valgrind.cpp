#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "gtest/gtest.h"
#include "tests_aux.h"

class place_tiles_invalid_valgrind_TestSuite : public testing::Test { 
    void SetUp() override {
        mkdir("./tests/actual_outputs/", 0700);
    }
};

TEST_F(place_tiles_invalid_valgrind_TestSuite, invalid_horiz_resize01_valgrind) {
    expect_no_valgrind_errors(run_using_valgrind("invalid_horiz_resize01_valgrind"));
}

TEST_F(place_tiles_invalid_valgrind_TestSuite, invalid_vert_overlap01_valgrind) {
    expect_no_valgrind_errors(run_using_valgrind("invalid_vert_overlap01_valgrind"));
}

TEST_F(place_tiles_invalid_valgrind_TestSuite, invalid_placement03_valgrind) {
    expect_no_valgrind_errors(run_using_valgrind("invalid_placement03_valgrind"));
}

TEST_F(place_tiles_invalid_valgrind_TestSuite, height_exceed_limit02_valgrind) {
    expect_no_valgrind_errors(run_using_valgrind("height_exceed_limit02_valgrind"));
}

TEST_F(place_tiles_invalid_valgrind_TestSuite, invalid_vert_touch04_valgrind) {
    expect_no_valgrind_errors(run_using_valgrind("invalid_vert_touch04_valgrind"));
}

TEST_F(place_tiles_invalid_valgrind_TestSuite, invalid_vert_touch08_valgrind) {
    expect_no_valgrind_errors(run_using_valgrind("invalid_vert_touch08_valgrind"));
}

TEST_F(place_tiles_invalid_valgrind_TestSuite, invalid_horiz_no_touch02_valgrind) {
    expect_no_valgrind_errors(run_using_valgrind("invalid_horiz_no_touch02_valgrind"));
}

