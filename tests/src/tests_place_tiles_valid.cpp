//To Test cd to upwords, cmake -S . -B build, cmake --build build, cd build, valgrind --leak-check=full ./run_all_tests
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "gtest/gtest.h"
#include "tests_aux.h"

extern "C" {
#include "hw3.h"
}

static const char *actual_filename = "./tests/actual_outputs/test_output.txt";
static int num_tiles_placed;

class place_tiles_TestSuite : public testing::Test { 
    void SetUp() override {
        system("rm -rf ./tests/actual_outputs");
        mkdir("./tests/actual_outputs/", 0700);
    }
};

TEST_F(place_tiles_TestSuite, place_one_tile01) {
    INFO("Several successful placements of tiles");
	GameState *game = initialize_game_state("./tests/boards/board01.txt"); 
    game = place_tiles(game, 3, 2, 'H', "C", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 1);
    save_game_state(game, actual_filename);

    const char *expected_filename = "./tests/expected_outputs/place_one_tile01.txt"; 
    char *expected_output = load_file(expected_filename);
    char *actual_output = load_file(actual_filename);
    EXPECT_STREQ(expected_output, actual_output);

    free(expected_output);
    free(actual_output);
    free_game_state(game);
}

TEST_F(place_tiles_TestSuite, place_several_tiles01) {
    INFO("Several successful placements of tiles");
	GameState *game = initialize_game_state("./tests/boards/board01.txt"); 
    game = place_tiles(game, 3, 2, 'H', "T Z E", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 3);
    save_game_state(game, actual_filename);

    const char *expected_filename = "./tests/expected_outputs/place_several_tiles01.txt"; 
    char *expected_output = load_file(expected_filename);
    char *actual_output = load_file(actual_filename);
    EXPECT_STREQ(expected_output, actual_output);

    free(expected_output);
    free(actual_output);
    free_game_state(game);
}

TEST_F(place_tiles_TestSuite,place_vertical_word01) {
    INFO("Several successful placements of tiles");
	GameState *game = initialize_game_state("./tests/boards/board01.txt"); 
    game = place_tiles(game, 0, 2, 'V', "UNICED", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 6);
    save_game_state(game, actual_filename);

    const char *expected_filename = "./tests/expected_outputs/place_vertical_word01.txt"; 
    char *expected_output = load_file(expected_filename);
    char *actual_output = load_file(actual_filename);
    EXPECT_STREQ(expected_output, actual_output);

    free(expected_output);
    free(actual_output);
    free_game_state(game);
}

TEST_F(place_tiles_TestSuite,place_vertical_word02) {
    INFO("Several successful placements of tiles");
	GameState *game = initialize_game_state("./tests/boards/board01.txt"); 
    game = place_tiles(game, 0, 2, 'V', "UNUSURPING", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 10);
    save_game_state(game, actual_filename);

    const char *expected_filename = "./tests/expected_outputs/place_vertical_word02.txt"; 
    char *expected_output = load_file(expected_filename);
    char *actual_output = load_file(actual_filename);
    EXPECT_STREQ(expected_output, actual_output);

    free(expected_output);
    free(actual_output);
    free_game_state(game);
}

TEST_F(place_tiles_TestSuite,place_vertical_word03) {
    INFO("Several successful placements of tiles");
	GameState *game = initialize_game_state("./tests/boards/board01.txt"); 
    game = place_tiles(game, 0, 5, 'V', "ABS NCE", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 6);
    save_game_state(game, actual_filename);

    const char *expected_filename = "./tests/expected_outputs/place_vertical_word03.txt"; 
    char *expected_output = load_file(expected_filename);
    char *actual_output = load_file(actual_filename);
    EXPECT_STREQ(expected_output, actual_output);

    free(expected_output);
    free(actual_output);
    free_game_state(game);
}

TEST_F(place_tiles_TestSuite,place_vertical_word04) {
    INFO("Several successful placements of tiles");
	GameState *game = initialize_game_state("./tests/boards/board01.txt"); 
    game = place_tiles(game, 0, 5, 'V', "ABROGATION", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 10);
    save_game_state(game, actual_filename);

    const char *expected_filename = "./tests/expected_outputs/place_vertical_word04.txt"; 
    char *expected_output = load_file(expected_filename);
    char *actual_output = load_file(actual_filename);
    EXPECT_STREQ(expected_output, actual_output);

    free(expected_output);
    free(actual_output);
    free_game_state(game);
}

TEST_F(place_tiles_TestSuite,place_vertical_word05) {
    INFO("Several successful placements of tiles");
	GameState *game = initialize_game_state("./tests/boards/board01.txt"); 
    game = place_tiles(game, 2, 4, 'V', "E", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 1);
    save_game_state(game, actual_filename);

    const char *expected_filename = "./tests/expected_outputs/place_vertical_word05.txt"; 
    char *expected_output = load_file(expected_filename);
    char *actual_output = load_file(actual_filename);
    EXPECT_STREQ(expected_output, actual_output);

    free(expected_output);
    free(actual_output);
    free_game_state(game);
}

TEST_F(place_tiles_TestSuite,place_vertical_word06) {
    INFO("Several successful placements of tiles");
	GameState *game = initialize_game_state("./tests/boards/board01.txt"); 
    game = place_tiles(game, 1, 4, 'V', "CA ARADERIE", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 10);
    save_game_state(game, actual_filename);

    const char *expected_filename = "./tests/expected_outputs/place_vertical_word06.txt"; 
    char *expected_output = load_file(expected_filename);
    char *actual_output = load_file(actual_filename);
    EXPECT_STREQ(expected_output, actual_output);

    free(expected_output);
    free(actual_output);
    free_game_state(game);
}

TEST_F(place_tiles_TestSuite, place_vertical_word07) {
     INFO("Several successful placements of tiles");
	GameState *game = initialize_game_state("./tests/boards/board06.txt");
    game = place_tiles(game, 2, 2, 'V', "LI TLESSNESS", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 11);
    save_game_state(game, actual_filename);

    const char *expected_filename = "./tests/expected_outputs/place_vertical_word07.txt";  
    char *expected_output = load_file(expected_filename);
    char *actual_output = load_file(actual_filename);
    EXPECT_STREQ(expected_output, actual_output);

    free(expected_output);
    free(actual_output);
    free_game_state(game);
}


TEST_F(place_tiles_TestSuite, place_vertical_word08) {
     INFO("Several successful placements of tiles");
	GameState *game = initialize_game_state("./tests/boards/board08.txt");
    game = place_tiles(game, 7, 2, 'V', " LAYGROUND", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 9);
    save_game_state(game, actual_filename);

    const char *expected_filename = "./tests/expected_outputs/place_vertical_word08.txt";  
    char *expected_output = load_file(expected_filename);
    char *actual_output = load_file(actual_filename);
    EXPECT_STREQ(expected_output, actual_output);

    free(expected_output);
    free(actual_output);
    free_game_state(game);
}

TEST_F(place_tiles_TestSuite,place_horizontal_word01) {
    INFO("Several successful placements of tiles");
	GameState *game = initialize_game_state("./tests/boards/board05.txt"); 
    game = place_tiles(game, 2, 3, 'H', "CA LE", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 4);
    save_game_state(game, actual_filename);

    const char *expected_filename = "./tests/expected_outputs/place_horizontal_word01.txt"; 
    char *expected_output = load_file(expected_filename);
    char *actual_output = load_file(actual_filename);
    EXPECT_STREQ(expected_output, actual_output);

    free(expected_output);
    free(actual_output);
    free_game_state(game);
}

TEST_F(place_tiles_TestSuite,place_horizontal_word02) {
    INFO("Several successful placements of tiles");
	GameState *game = initialize_game_state("./tests/boards/board05.txt"); 
    game = place_tiles(game, 2, 5, 'H', " ACHELOR", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 7);
    save_game_state(game, actual_filename);

    const char *expected_filename = "./tests/expected_outputs/place_horizontal_word02.txt"; 
    char *expected_output = load_file(expected_filename);
    char *actual_output = load_file(actual_filename);
    EXPECT_STREQ(expected_output, actual_output);

    free(expected_output);
    free(actual_output);
    free_game_state(game);
}

TEST_F(place_tiles_TestSuite,place_horizontal_word03) {
    INFO("Several successful placements of tiles");
	GameState *game = initialize_game_state("./tests/boards/board05.txt"); 
    game = place_tiles(game, 6, 4, 'H', "ADAMANT", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 7);
    save_game_state(game, actual_filename);

    const char *expected_filename = "./tests/expected_outputs/place_horizontal_word03.txt"; 
    char *expected_output = load_file(expected_filename);
    char *actual_output = load_file(actual_filename);
    EXPECT_STREQ(expected_output, actual_output);

    free(expected_output);
    free(actual_output);
    free_game_state(game);
}

TEST_F(place_tiles_TestSuite,place_horizontal_word04) {
    INFO("Several successful placements of tiles");
	GameState *game = initialize_game_state("./tests/boards/board05.txt"); 
    game = place_tiles(game, 6, 4, 'H', "S ELETON", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 7);
    save_game_state(game, actual_filename);

    const char *expected_filename = "./tests/expected_outputs/place_horizontal_word04.txt"; 
    char *expected_output = load_file(expected_filename);
    char *actual_output = load_file(actual_filename);
    EXPECT_STREQ(expected_output, actual_output);

    free(expected_output);
    free(actual_output);
    free_game_state(game);
}

TEST_F(place_tiles_TestSuite,place_horizontal_word05) {
    INFO("Several successful placements of tiles");
	GameState *game = initialize_game_state("./tests/boards/board05.txt"); 
    game = place_tiles(game, 4, 4, 'H', "T G", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 2);
    game = place_tiles(game, 5, 4, 'H', "H OK", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 3);
    save_game_state(game, actual_filename);

    const char *expected_filename = "./tests/expected_outputs/place_horizontal_word05.txt"; 
    char *expected_output = load_file(expected_filename);
    char *actual_output = load_file(actual_filename);
    EXPECT_STREQ(expected_output, actual_output);

    free(expected_output);
    free(actual_output);
    free_game_state(game);
}

TEST_F(place_tiles_TestSuite,place_horizontal_word06) {
    INFO("Several successful placements of tiles");
	GameState *game = initialize_game_state("./tests/boards/board05.txt"); 
    game = place_tiles(game, 5, 3, 'H', "UNCARNIVOROUS", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 13);
    save_game_state(game, actual_filename);

    const char *expected_filename = "./tests/expected_outputs/place_horizontal_word06.txt"; 
    char *expected_output = load_file(expected_filename);
    char *actual_output = load_file(actual_filename);
    EXPECT_STREQ(expected_output, actual_output);

    free(expected_output);
    free(actual_output);
    free_game_state(game);
}

TEST_F(place_tiles_TestSuite,place_horizontal_word07) {
    INFO("Several successful placements of tiles");
	GameState *game = initialize_game_state("./tests/boards/board08.txt"); 
    game = place_tiles(game, 6, 12, 'H', " ROID", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 4);
    save_game_state(game, actual_filename);

    const char *expected_filename = "./tests/expected_outputs/place_horizontal_word07.txt"; 
    char *expected_output = load_file(expected_filename);
    char *actual_output = load_file(actual_filename);
    EXPECT_STREQ(expected_output, actual_output);

    free(expected_output);
    free(actual_output);
    free_game_state(game);
}


TEST_F(place_tiles_TestSuite,initialize_big_board) {
    INFO("Several initialize a big board");
	GameState *game = initialize_game_state("./tests/boards/board09.txt"); 
    save_game_state(game, actual_filename);

    const char *expected_filename = "./tests/expected_outputs/big_board.txt"; 
    char *expected_output = load_file(expected_filename);
    char *actual_output = load_file(actual_filename);
    EXPECT_STREQ(expected_output, actual_output);

    free(expected_output);
    free(actual_output);
    free_game_state(game);
}
