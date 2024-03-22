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

class undo_place_tiles_TestSuite : public testing::Test { 
    void SetUp() override {
        system("rm -rf ./tests/actual_outputs");
        mkdir("./tests/actual_outputs/", 0700);
    }
};

TEST_F(undo_place_tiles_TestSuite, undo01) {
    INFO("Successful undo operation");
	GameState *game = initialize_game_state("./tests/boards/board01.txt"); 
    game = place_tiles(game, 2, 3, 'V', "T PMAN", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 5);
    game = place_tiles(game, 2, 5, 'V', "P TAL", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 4);
    game = place_tiles(game, 6, 1, 'H', "SN I", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 3);
    game = undo_place_tiles(game);
    save_game_state(game, actual_filename);

    const char *expected_filename = "./tests/expected_outputs/undo01.txt"; 
    char *expected_output = load_file(expected_filename);
    char *actual_output = load_file(actual_filename);
    EXPECT_STREQ(expected_output, actual_output);

    free(expected_output);
    free(actual_output);
    free_game_state(game);
}

TEST_F(undo_place_tiles_TestSuite, undo02) {
    INFO("Successful undo operation");
	GameState *game = initialize_game_state("./tests/boards/board2x2.txt");
    game = place_tiles(game, 0, 0, 'H', "CAT", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 3);
    game = place_tiles(game, 0, 0, 'V', " AR", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 2);
    game = undo_place_tiles(game);
    game = undo_place_tiles(game);
    save_game_state(game, actual_filename);

    const char *expected_filename = "./tests/expected_outputs/undo02.txt"; 
    char *expected_output = load_file(expected_filename);
    char *actual_output = load_file(actual_filename);
    EXPECT_STREQ(expected_output, actual_output);

    free(expected_output);
    free(actual_output);
    free_game_state(game);
}

TEST_F(undo_place_tiles_TestSuite, undo03) {
    //Undo resize. 
    INFO("Successful undo operation");
	GameState *game = initialize_game_state("./tests/boards/board01.txt"); 
    game = place_tiles(game, 2, 3, 'V', "T XIPHOBIA", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 9);
    game = undo_place_tiles(game);
    save_game_state(game, actual_filename);

    const char *expected_filename = "./tests/expected_outputs/undo04.txt"; 
    char *expected_output = load_file(expected_filename);
    char *actual_output = load_file(actual_filename);
    EXPECT_STREQ(expected_output, actual_output);

    free(expected_output);
    free(actual_output);
    free_game_state(game);
}

TEST_F(undo_place_tiles_TestSuite, undo04) {
    //Test undo initial state
    INFO("Successful undo operation");
	GameState *game = initialize_game_state("./tests/boards/board01.txt"); 
    game = undo_place_tiles(game);
    save_game_state(game, actual_filename);

    const char *expected_filename = "./tests/expected_outputs/undo04.txt"; 
    char *expected_output = load_file(expected_filename);
    char *actual_output = load_file(actual_filename);
    EXPECT_STREQ(expected_output, actual_output);

    free(expected_output);
    free(actual_output);
    free_game_state(game);
}

TEST_F(undo_place_tiles_TestSuite, undo05) {
    //Test undo initial state
    INFO("Successful undo operation");
	GameState *game = initialize_game_state("./tests/boards/board2x2.txt");
    game = place_tiles(game, 0, 0, 'H', "CAT", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 3);
    game = place_tiles(game, 0, 3, 'H', "ASTROPHE", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 0);
    game = place_tiles(game, 0, 2 ,'H', " ASTROPHE", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 8);
    game = place_tiles(game, 1, 1 ,'V', "STRONAUT", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 8);
    game = undo_place_tiles(game);
    game = undo_place_tiles(game);
    game = place_tiles(game, 0, 0, 'H', "DOG", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 0);
    game = undo_place_tiles(game);
    save_game_state(game, actual_filename);

    const char *expected_filename = "./tests/expected_outputs/undo02.txt"; 
    char *expected_output = load_file(expected_filename);
    char *actual_output = load_file(actual_filename);
    EXPECT_STREQ(expected_output, actual_output);

    free(expected_output);
    free(actual_output);
    free_game_state(game);
}

TEST_F(undo_place_tiles_TestSuite, undo06) {
    //Test undo initial state
    INFO("Successful undo operation");
	GameState *game = initialize_game_state("./tests/boards/board06.txt");
    game = undo_place_tiles(game);
    game = place_tiles(game, 8, 5, 'V', "SOME", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 4);
    game = place_tiles(game, 9, 17, 'V', "ABBAGE", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 6);
    game = place_tiles(game, 0, 0, 'H', "CAT", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 0);
    game = place_tiles(game, 8, 5, 'V', "SOME", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 0);
    game = place_tiles(game, 10, 5, 'H', " ANGANOCOLUM ITE", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 14);
    game = place_tiles(game, 10, 5, 'H', "HOME", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 0);
    game = undo_place_tiles(game);
    game = undo_place_tiles(game);
    game = undo_place_tiles(game);
    save_game_state(game, actual_filename);

    const char *expected_filename = "./tests/expected_outputs/undo06.txt"; 
    char *expected_output = load_file(expected_filename);
    char *actual_output = load_file(actual_filename);
    EXPECT_STREQ(expected_output, actual_output);

    free(expected_output);
    free(actual_output);
    free_game_state(game);
}



