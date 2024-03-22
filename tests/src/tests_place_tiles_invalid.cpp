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

TEST_F(place_tiles_TestSuite, invalid_horiz_resize01) {
    INFO("Verifying board is not resized due to illegal placement.");
	GameState *game = initialize_game_state("./tests/boards/board04.txt");
    game = place_tiles(game, 4, 19, 'H', "INSERT", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 0);
    save_game_state(game, actual_filename);

    const char *expected_filename = "./tests/expected_outputs/do_not_resize01.txt"; 
    char *expected_output = load_file(expected_filename);
    char *actual_output = load_file(actual_filename);
    EXPECT_STREQ(expected_output, actual_output);

    free(expected_output);
    free(actual_output);
    free_game_state(game);
}

TEST_F(place_tiles_TestSuite, invalid_horiz_overlap01) {
    INFO("Attempt to cover all the tiles of an existing horizontal word with the same tiles.");
	GameState *game = initialize_game_state("./tests/boards/board04.txt");
    game = place_tiles(game, 6, 11, 'H', "SNEER", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 0);
    save_game_state(game, actual_filename);

    const char *expected_filename = "./tests/expected_outputs/invalid_horiz_overlap01.txt"; 
    char *expected_output = load_file(expected_filename);
    char *actual_output = load_file(actual_filename);
    EXPECT_STREQ(expected_output, actual_output);

    free(expected_output);
    free(actual_output);
    free_game_state(game);
}

TEST_F(place_tiles_TestSuite, invalid_horiz_overlap02) {
    INFO("Attempt to cover some of the tiles of an existing horizontal word with the same tiles without making a new word.");
	GameState *game = initialize_game_state("./tests/boards/board04.txt");
    game = place_tiles(game, 6, 14, 'H', "ER", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 0);
    save_game_state(game, actual_filename);

    const char *expected_filename = "./tests/expected_outputs/invalid_horiz_overlap02.txt"; 
    char *expected_output = load_file(expected_filename);
    char *actual_output = load_file(actual_filename);
    EXPECT_STREQ(expected_output, actual_output);

    free(expected_output);
    free(actual_output);
    free_game_state(game);
}

TEST_F(place_tiles_TestSuite, invalid_vert_overlap01) {
    INFO("Attempt to cover all the tiles of an existing vertical word with the same tiles.");
	GameState *game = initialize_game_state("./tests/boards/board04.txt");
    game = place_tiles(game, 4, 12, 'V', "DINGO", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 0);
    save_game_state(game, actual_filename);

    const char *expected_filename = "./tests/expected_outputs/invalid_vert_overlap01.txt"; 
    char *expected_output = load_file(expected_filename);
    char *actual_output = load_file(actual_filename);
    EXPECT_STREQ(expected_output, actual_output);

    free(expected_output);
    free(actual_output);
    free_game_state(game);
}

TEST_F(place_tiles_TestSuite, invalid_vert_overlap02) {
    INFO("Attempt to cover some the tiles of an existing vertical word with the same tiles.");
	GameState *game = initialize_game_state("./tests/boards/board04.txt");
    game = place_tiles(game, 2, 7, 'V', "H B ID", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 0);
    save_game_state(game, actual_filename);

    const char *expected_filename = "./tests/expected_outputs/invalid_vert_overlap02.txt"; 
    char *expected_output = load_file(expected_filename);
    char *actual_output = load_file(actual_filename);
    EXPECT_STREQ(expected_output, actual_output);

    free(expected_output);
    free(actual_output);
    free_game_state(game);
}

TEST_F(place_tiles_TestSuite, invalid_placement01) {
    INFO("First word must contain at least two letters.");
	GameState *game = initialize_game_state("./tests/boards/board02.txt");
    game = place_tiles(game, 0, 0, 'H', "I", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 0);
    
    save_game_state(game, actual_filename);

    const char *expected_filename = "./tests/expected_outputs/invalid_placement01.txt"; 
    char *expected_output = load_file(expected_filename);
    char *actual_output = load_file(actual_filename);
    EXPECT_STREQ(expected_output, actual_output);

    free(expected_output);
    free(actual_output);
    free_game_state(game);
}

TEST_F(place_tiles_TestSuite, invalid_placement02) {
    INFO("Attempt to place the same letter.");
	GameState *game = initialize_game_state("./tests/boards/board02.txt");
    game = place_tiles(game, 0, 0, 'H', "CAT", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 3);
    game = place_tiles(game, 0, 0, 'H', "TOT", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 0);
    save_game_state(game, actual_filename);

    const char *expected_filename = "./tests/expected_outputs/invalid_placement02.txt"; 
    char *expected_output = load_file(expected_filename);
    char *actual_output = load_file(actual_filename);
    EXPECT_STREQ(expected_output, actual_output);

    free(expected_output);
    free(actual_output);
    free_game_state(game);
}

TEST_F(place_tiles_TestSuite, invalid_placement03) {
    INFO("Attempt to cover the complete existing tile");
	GameState *game = initialize_game_state("./tests/boards/board02.txt");
    game = place_tiles(game, 0, 0, 'H', "CAT", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 3);
    game = place_tiles(game, 0, 0, 'H', "DOG", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 0);
    save_game_state(game, actual_filename);

    const char *expected_filename = "./tests/expected_outputs/invalid_placement02.txt"; 
    char *expected_output = load_file(expected_filename);
    char *actual_output = load_file(actual_filename);
    EXPECT_STREQ(expected_output, actual_output);

    free(expected_output);
    free(actual_output);
    free_game_state(game);
}

TEST_F(place_tiles_TestSuite, invalid_placement04) {
    INFO("Attempt to place a word without using an existing tile");
	GameState *game = initialize_game_state("./tests/boards/board05.txt");
    game = place_tiles(game, 0, 0, 'H', "CAT", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 0);
    save_game_state(game, actual_filename);

    const char *expected_filename = "./tests/expected_outputs/invalid_placement04.txt"; 
    char *expected_output = load_file(expected_filename);
    char *actual_output = load_file(actual_filename);
    EXPECT_STREQ(expected_output, actual_output);

    free(expected_output);
    free(actual_output);
    free_game_state(game);
}

TEST_F(place_tiles_TestSuite, height_exceed_limit01)
{   
    INFO("Checking that height of a stack does not exceed 5.");
	GameState *game = initialize_game_state("./tests/boards/board02.txt"); 
    game = place_tiles(game,0 , 0, 'H', "CANDY", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 5) << "Placing tiles failed."; 
    game = place_tiles(game,0 , 0, 'H', "R", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 1) << "Placing tiles failed."; 
    game = place_tiles(game,0 , 0, 'H', "B", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 1) << "Placing tiles failed."; 
    game = place_tiles(game,0 , 0, 'H', "S", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 1) << "Placing tiles failed."; 
    game = place_tiles(game,0 , 0, 'H', "H", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 1) << "Placing tiles failed."; 
    game = place_tiles(game,0 , 0, 'H', "D", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 0) << "Height exceeds the maximum allowed"; 
    save_game_state(game, actual_filename);

    const char *expected_filename = "./tests/expected_outputs/height_exceed_limit01.txt"; 
    char *expected_output = load_file(expected_filename);
    char *actual_output = load_file(actual_filename);
    EXPECT_STREQ(expected_output, actual_output);

    free(expected_output);
    free(actual_output);
    free_game_state(game);
}

TEST_F(place_tiles_TestSuite, height_exceed_limit02)
{   
    INFO("Checking that height of a stack does not exceed 5.");
	GameState *game = initialize_game_state("./tests/boards/board02.txt"); 
    game = place_tiles(game,0 , 0, 'V', "ARABLE", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 6) << "Placing tiles failed."; 
    game = place_tiles(game,0 , 0, 'V', "DO", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 2) << "Placing tiles failed."; 
    game = place_tiles(game,0 , 0, 'V', "EN", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 2) << "Placing tiles failed."; 
    game = place_tiles(game,0 , 0, 'V', "LI", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 2) << "Placing tiles failed."; 
    game = place_tiles(game,0 , 0, 'V', "ME", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 2) << "Placing tiles failed."; 
    game = place_tiles(game,0 , 0, 'V', "ST", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 0) << "Height exceeds the maximum allowed"; 
    save_game_state(game, actual_filename);

    const char *expected_filename = "./tests/expected_outputs/height_exceed_limit02.txt"; 
    char *expected_output = load_file(expected_filename);
    char *actual_output = load_file(actual_filename);
    EXPECT_STREQ(expected_output, actual_output);

    free(expected_output);
    free(actual_output);
    free_game_state(game);
}

TEST_F(place_tiles_TestSuite, invalid_vert_no_touch01) {
    INFO("Attempt to place a word vertically that does not touch another.");
	GameState *game = initialize_game_state("./tests/boards/board04.txt");
    game = place_tiles(game, 5, 19, 'V', "TREAT", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 0);
    save_game_state(game, actual_filename);

    const char *expected_filename = "./tests/expected_outputs/invalid_vert_no_touch01.txt"; 
    char *expected_output = load_file(expected_filename);
    char *actual_output = load_file(actual_filename);
    EXPECT_STREQ(expected_output, actual_output);

    free(expected_output);
    free(actual_output);
    free_game_state(game);
}

TEST_F(place_tiles_TestSuite, invalid_vert_no_touch02) {
    INFO("Attempt to place a word vertically that does not touch another.");
	GameState *game = initialize_game_state("./tests/boards/board04.txt");
    game = place_tiles(game, 8, 18, 'V', "TREAT", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 0);
    save_game_state(game, actual_filename);

    const char *expected_filename = "./tests/expected_outputs/invalid_vert_no_touch02.txt"; 
    char *expected_output = load_file(expected_filename);
    char *actual_output = load_file(actual_filename);
    EXPECT_STREQ(expected_output, actual_output);

    free(expected_output);
    free(actual_output);
    free_game_state(game);
}

TEST_F(place_tiles_TestSuite, invalid_horiz_no_touch01) {
    INFO("Attempt to place a word horizontally that does not touch another.");
	GameState *game = initialize_game_state("./tests/boards/board04.txt");
    game = place_tiles(game, 7, 16, 'H', "HARP", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 0);
    save_game_state(game, actual_filename);

    const char *expected_filename = "./tests/expected_outputs/invalid_horiz_no_touch01.txt"; 
    char *expected_output = load_file(expected_filename);
    char *actual_output = load_file(actual_filename);
    EXPECT_STREQ(expected_output, actual_output);

    free(expected_output);
    free(actual_output);
    free_game_state(game);
}

TEST_F(place_tiles_TestSuite, invalid_horiz_no_touch02) {
    INFO("Attempt to place a word horizontally that does not touch another.");
	GameState *game = initialize_game_state("./tests/boards/board04.txt");
    game = place_tiles(game, 7, 17, 'H', "HOODIE", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 0);
    save_game_state(game, actual_filename);

    const char *expected_filename = "./tests/expected_outputs/invalid_horiz_no_touch02.txt"; 
    char *expected_output = load_file(expected_filename);
    char *actual_output = load_file(actual_filename);
    EXPECT_STREQ(expected_output, actual_output);

    free(expected_output);
    free(actual_output);
    free_game_state(game);
}

TEST_F(place_tiles_TestSuite, invalid_vert_touch01) {
    INFO("Attempt to place tiles vertically that touch the leftmost tile of an existing horizontal word and do not form a legal word.");
	GameState *game = initialize_game_state("./tests/boards/board06.txt");
    game = place_tiles(game, 3, 1, 'V', "DRINK", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 0);
    save_game_state(game, actual_filename);

    const char *expected_filename = "./tests/expected_outputs/invalid_vert_touch01.txt"; 
    char *expected_output = load_file(expected_filename);
    char *actual_output = load_file(actual_filename);
    EXPECT_STREQ(expected_output, actual_output);

    free(expected_output);
    free(actual_output);
    free_game_state(game);
}

TEST_F(place_tiles_TestSuite, invalid_vert_touch02) {
    INFO("Attempt to place tiles vertically that touch the leftmost tile of an existing horizontal word and do not form a legal word.");
	GameState *game = initialize_game_state("./tests/boards/board06.txt");
    game = place_tiles(game, 2, 1, 'V', "LITERATE", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 0);
    save_game_state(game, actual_filename);

    const char *expected_filename = "./tests/expected_outputs/invalid_vert_touch02.txt"; 
    char *expected_output = load_file(expected_filename);
    char *actual_output = load_file(actual_filename);
    EXPECT_STREQ(expected_output, actual_output);

    free(expected_output);
    free(actual_output);
    free_game_state(game);
}

TEST_F(place_tiles_TestSuite, invalid_vert_touch03) {
    INFO("Attempt to place tiles vertically that intersect an interior tile of an existing horizontal word and do not form a legal word.");
	GameState *game = initialize_game_state("./tests/boards/board03.txt");
    game = place_tiles(game, 2, 4, 'V', "E T", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 0);
    save_game_state(game, actual_filename);

    const char *expected_filename = "./tests/expected_outputs/invalid_vert_touch03.txt"; 
    char *expected_output = load_file(expected_filename);
    char *actual_output = load_file(actual_filename);
    EXPECT_STREQ(expected_output, actual_output);

    free(expected_output);
    free(actual_output);
    free_game_state(game);
}

TEST_F(place_tiles_TestSuite, invalid_vert_touch04) {
    INFO("Attempt to place tiles vertically that intersect two existing horizontal words and do not form a legal word.");
	GameState *game = initialize_game_state("./tests/boards/board08.txt");
    game = place_tiles(game, 1, 6, 'V', " E R ", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 0);
    save_game_state(game, actual_filename);

    const char *expected_filename = "./tests/expected_outputs/invalid_vert_touch04.txt"; 
    char *expected_output = load_file(expected_filename);
    char *actual_output = load_file(actual_filename);
    EXPECT_STREQ(expected_output, actual_output);

    free(expected_output);
    free(actual_output);
    free_game_state(game);
}

TEST_F(place_tiles_TestSuite, invalid_vert_touch05) {
    INFO("Attempt to place tiles vertically that touch the rightmost tile of an existing horizontal word and do not form a legal word.");
	GameState *game = initialize_game_state("./tests/boards/board08.txt");
    game = place_tiles(game, 0, 11, 'V', "ZOO", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 0);
    save_game_state(game, actual_filename);

    const char *expected_filename = "./tests/expected_outputs/invalid_vert_touch04.txt"; 
    char *expected_output = load_file(expected_filename);
    char *actual_output = load_file(actual_filename);
    EXPECT_STREQ(expected_output, actual_output);

    free(expected_output);
    free(actual_output);
    free_game_state(game);
}

TEST_F(place_tiles_TestSuite, invalid_vert_touch06) {
    INFO("Attempt to place tiles vertically where a space in the input corresponds with a blank spot (.) on the board.");
	GameState *game = initialize_game_state("./tests/boards/board06.txt");
    game = place_tiles(game, 0, 12, 'V', "  AD E", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 0);
    save_game_state(game, actual_filename);

    const char *expected_filename = "./tests/expected_outputs/invalid_vert_touch06.txt"; 
    char *expected_output = load_file(expected_filename);
    char *actual_output = load_file(actual_filename);
    EXPECT_STREQ(expected_output, actual_output);

    free(expected_output);
    free(actual_output);
    free_game_state(game);
}


TEST_F(place_tiles_TestSuite, invalid_vert_touch07) {
    INFO("Attempt to place tiles vertically where a space in the input corresponds with a blank spot (.) on the board.");
	GameState *game = initialize_game_state("./tests/boards/board08.txt");
    game = place_tiles(game, 2, 6, 'V', " C", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 0);
    save_game_state(game, actual_filename);

    const char *expected_filename = "./tests/expected_outputs/invalid_vert_touch04.txt"; 
    char *expected_output = load_file(expected_filename);
    char *actual_output = load_file(actual_filename);
    EXPECT_STREQ(expected_output, actual_output);

    free(expected_output);
    free(actual_output);
    free_game_state(game);
}

TEST_F(place_tiles_TestSuite, invalid_vert_touch08) {
     INFO("Attempt to play tiles vertically that touch tiles on the right");
	GameState *game = initialize_game_state("./tests/boards/board08.txt");
    game = place_tiles(game, 8, 2, 'V', "LAYGROUND", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 0);
    save_game_state(game, actual_filename);

    const char *expected_filename = "./tests/expected_outputs/invalid_vert_touch04.txt";  
    char *expected_output = load_file(expected_filename);
    char *actual_output = load_file(actual_filename);
    EXPECT_STREQ(expected_output, actual_output);

    free(expected_output);
    free(actual_output);
    free_game_state(game);
}

TEST_F(place_tiles_TestSuite, invalid_horiz_touch01) {
    INFO("Attempt to place tiles horizontally that touch the topmost tile of an existing vertical word and do not form a legal word.");
	GameState *game = initialize_game_state("./tests/boards/board05.txt");
    game = place_tiles(game, 2, 6, 'H', "RO", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 0);
    save_game_state(game, actual_filename);

    const char *expected_filename = "./tests/expected_outputs/invalid_horiz_touch01.txt"; 
    char *expected_output = load_file(expected_filename);
    char *actual_output = load_file(actual_filename);
    EXPECT_STREQ(expected_output, actual_output);

    free(expected_output);
    free(actual_output);
    free_game_state(game);
}

TEST_F(place_tiles_TestSuite, invalid_horiz_touch02) {
    INFO("Attempt to place tiles horizontally that touch the bottommost tile of an existing vertical word and do not form a legal word.");
	GameState *game = initialize_game_state("./tests/boards/board05.txt");
    game = place_tiles(game, 6, 4, 'H', "TOP", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 0);
    save_game_state(game, actual_filename);

    const char *expected_filename = "./tests/expected_outputs/invalid_horiz_touch01.txt"; 
    char *expected_output = load_file(expected_filename);
    char *actual_output = load_file(actual_filename);
    EXPECT_STREQ(expected_output, actual_output);

    free(expected_output);
    free(actual_output);
    free_game_state(game);
}

TEST_F(place_tiles_TestSuite, invalid_horiz_touch03) {
    INFO("Attempt to place tiles horizontally  that intersect an interior tile of an existing vertical word and do not form a legal word.");
	GameState *game = initialize_game_state("./tests/boards/board05.txt");
    game = place_tiles(game, 5, 4, 'H', "TOP", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 0);
    game = place_tiles(game, 5, 3, 'H', "M P", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 0);
    save_game_state(game, actual_filename);

    const char *expected_filename = "./tests/expected_outputs/invalid_horiz_touch01.txt"; 
    char *expected_output = load_file(expected_filename);
    char *actual_output = load_file(actual_filename);
    EXPECT_STREQ(expected_output, actual_output);

    free(expected_output);
    free(actual_output);
    free_game_state(game);
}

TEST_F(place_tiles_TestSuite, invalid_horiz_touch04) {
    INFO("Attempt to place tiles horizontally that intersect two existing vertical words and do not form a legal word.");
	GameState *game = initialize_game_state("./tests/boards/board07.txt");
    game = place_tiles(game, 4, 0, 'H', "TO OOO OOO OOO", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 0);
    save_game_state(game, actual_filename);

    const char *expected_filename = "./tests/expected_outputs/invalid_horiz_touch04.txt"; 
    char *expected_output = load_file(expected_filename);
    char *actual_output = load_file(actual_filename);
    EXPECT_STREQ(expected_output, actual_output);

    free(expected_output);
    free(actual_output);
    free_game_state(game);
}

TEST_F(place_tiles_TestSuite, invalid_horiz_touch05) {
    INFO("Attempt to place tiles horizontally where a space in the input corresponds with a blank spot (.) on the board.");
	GameState *game = initialize_game_state("./tests/boards/board07.txt");
    game = place_tiles(game, 2, 3, 'H', " CA ", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 0);
    save_game_state(game, actual_filename);

    const char *expected_filename = "./tests/expected_outputs/invalid_horiz_touch04.txt"; 
    char *expected_output = load_file(expected_filename);
    char *actual_output = load_file(actual_filename);
    EXPECT_STREQ(expected_output, actual_output);

    free(expected_output);
    free(actual_output);
    free_game_state(game);
}

TEST_F(place_tiles_TestSuite, invalid_horiz_touch06) {
    INFO("Attempt to place tiles horizontally where a space in the input corresponds with a blank spot (.) on the board.");
	GameState *game = initialize_game_state("./tests/boards/board08.txt");
    game = place_tiles(game, 6, 12, 'H', " CANDY", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 0);
    save_game_state(game, actual_filename);

    const char *expected_filename = "./tests/expected_outputs/invalid_horiz_touch06.txt"; 
    char *expected_output = load_file(expected_filename);
    char *actual_output = load_file(actual_filename);
    EXPECT_STREQ(expected_output, actual_output);

    free(expected_output);
    free(actual_output);
    free_game_state(game);
}

TEST_F(place_tiles_TestSuite,invalid_horiz_touch07) {
    INFO("Invalid placement of tiles horizontally that run off the board");
	GameState *game = initialize_game_state("./tests/boards/board08.txt"); 
    game = place_tiles(game, 6, 13, 'H', "ROID", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 0);
    save_game_state(game, actual_filename);

    const char *expected_filename = "./tests/expected_outputs/invalid_horiz_touch06.txt"; 
    char *expected_output = load_file(expected_filename);
    char *actual_output = load_file(actual_filename);
    EXPECT_STREQ(expected_output, actual_output);

    free(expected_output);
    free(actual_output);
    free_game_state(game);
}



