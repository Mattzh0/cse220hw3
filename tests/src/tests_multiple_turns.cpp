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

class multiple_turns_TestSuite : public testing::Test { 
    void SetUp() override {
        system("rm -rf ./tests/actual_outputs");
        mkdir("./tests/actual_outputs/", 0700);
    }
};

TEST_F(multiple_turns_TestSuite, multiple01) {
    INFO("Several successful placements of tiles");
	GameState *game = initialize_game_state("./tests/boards/board01.txt"); 
    game = place_tiles(game, 2, 3, 'V', "T PMAN", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 5);
    game = place_tiles(game, 2, 5, 'V', "P TAL", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 4);
    game = place_tiles(game, 6, 1, 'H', "SN I", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 3);
    save_game_state(game, actual_filename);

    const char *expected_filename = "./tests/expected_outputs/multiple01.txt"; 
    char *expected_output = load_file(expected_filename);
    char *actual_output = load_file(actual_filename);
    EXPECT_STREQ(expected_output, actual_output);

    free(expected_output);
    free(actual_output);
    free_game_state(game);
}

TEST_F(multiple_turns_TestSuite, multiple02) {
    INFO("Several successful placements of tiles");
	GameState *game = initialize_game_state("./tests/boards/board01.txt"); 
    game = place_tiles(game, 2, 3, 'V', "T PMAN", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 5);
    game = place_tiles(game, 2, 5, 'V', "P TAL", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 4);
    game = place_tiles(game, 6, 1, 'H', "SN I", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 3);
    game = place_tiles(game, 2, 5, 'H', "M", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 1);
    game = place_tiles(game, 2, 6, 'H', "OON", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 3);
    save_game_state(game, actual_filename);

    const char *expected_filename = "./tests/expected_outputs/multiple02.txt"; 
    char *expected_output = load_file(expected_filename);
    char *actual_output = load_file(actual_filename);
    EXPECT_STREQ(expected_output, actual_output);

    free(expected_output);
    free(actual_output);
    free_game_state(game);
}

TEST_F(multiple_turns_TestSuite, multiple03)
{
    INFO("Several successful placements of tiles");
	GameState *game = initialize_game_state("./tests/boards/board01.txt");
    game = place_tiles(game, 2, 3, 'V', "T P", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 2) << "Placing tiles failed."; 
    game = place_tiles(game, 2, 5, 'V', "P T", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 2) << "Placing tiles failed."; 

    save_game_state(game, actual_filename);

    const char *expected_filename = "./tests/expected_outputs/multiple03.txt"; 
    char *expected_output = load_file(expected_filename);
    char *actual_output = load_file(actual_filename);
    EXPECT_STREQ(expected_output, actual_output);

    free(expected_output);
    free(actual_output);
    free_game_state(game);
}

TEST_F(multiple_turns_TestSuite, multiple04)
{
    INFO("Several successful placements of tiles");
	GameState *game = initialize_game_state("./tests/boards/board02.txt");
    game = place_tiles(game, 4, 5, 'H', "BRAMBLEBERRY", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 12);
    game = undo_place_tiles(game);
    game = place_tiles(game, 4, 5, 'V', "BRAMBLEBERRY", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 12);
    game = place_tiles(game, 5, 2, 'H', "BEA ABLE", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 7);
    game = place_tiles(game, 5, 1, 'H', "CL", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 2);
    game = place_tiles(game, 5, 6, 'H', "ANCE", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 0);
    game = place_tiles(game, 5, 7, 'H', "NC", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 2);
    game = place_tiles(game, 3, 8, 'V', "EX ELLENCE", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 9);    
    game = place_tiles(game, 10, 3, 'H', "AB RU CATOR", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 9);  
    game = place_tiles(game, 8, 3, 'H', "EM EL ISHMENT", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 11); 
    game = undo_place_tiles(game);
    game = place_tiles(game, 8, 3, 'H', "EM AL ONURIDAE", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 12); 
    game = place_tiles(game, 5, 1, 'H', "AB", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 2); 

    save_game_state(game, actual_filename);

    const char *expected_filename = "./tests/expected_outputs/multiple04.txt"; 
    char *expected_output = load_file(expected_filename);
    char *actual_output = load_file(actual_filename);
    EXPECT_STREQ(expected_output, actual_output);

    free(expected_output);
    free(actual_output);
    free_game_state(game);
}

TEST_F(multiple_turns_TestSuite, multiple05)
{
    INFO("Several successful placements of tiles");
	GameState *game = initialize_game_state("./tests/boards/board02.txt");

    game = place_tiles(game, 0, 0, 'H', "C", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 0) << "First word must more than two letters."; 
    game = place_tiles(game, 0, 0, 'H', "CAT", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 3) << "Placing tiles failed."; 
    game = place_tiles(game, 0, 1, 'H', "DOG", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 0) << "Placment is not rejected due to invalid overlap"; 
    game = place_tiles(game, 0, 0, 'V', " AR", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 2) << "Placing tiles failed."; 
    game = place_tiles(game, 0, 0, 'V', "   NIVAL", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 5) << "Placing tiles failed."; 
    game = place_tiles(game, 0, 0, 'H', "   ABASES", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 6) << "Placing tiles failed."; 
    game = place_tiles(game, 0, 7, 'V', " ARPHONE", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 7) << "Placing tiles failed."; 
    game = place_tiles(game, 7, 0, 'H', " ACERAT ", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 6) << "Placing tiles failed."; 
    game = undo_place_tiles(game);
    game = place_tiles(game, 7, 0, 'H', " IGHTKE PER", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 9) << "Placing tiles failed."; 
    game = place_tiles(game, 0, 0, 'H', "  BDRIV R", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 6) << "Placing tiles failed."; 

    save_game_state(game, actual_filename);

    const char *expected_filename = "./tests/expected_outputs/multiple05.txt"; 
    char *expected_output = load_file(expected_filename);
    char *actual_output = load_file(actual_filename);
    EXPECT_STREQ(expected_output, actual_output);

    free(expected_output);
    free(actual_output);
    free_game_state(game);
}

TEST_F(multiple_turns_TestSuite, multiple06)
{
    INFO("Several successful placements of tiles");
	GameState *game = initialize_game_state("./tests/boards/board2x2.txt");
    game = place_tiles(game, 0, 0, 'V', "ABDOMINOPOSTERIOR", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 17);
    game = place_tiles(game, 2, 0, 'H', " INER", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 4);
    game = place_tiles(game, 2, 4, 'H', "URIC", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 4);
    game = place_tiles(game, 1, 5, 'H', "OH", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 2);
    game = place_tiles(game, 3, 7, 'V', "ARE", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 3);
    game = place_tiles(game, 5, 4, 'H', "TAK", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 3);
    game = place_tiles(game, 5, 4, 'H', "B   D", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 2);
    game = undo_place_tiles(game);
    game = undo_place_tiles(game);
    game = undo_place_tiles(game);
    game = place_tiles(game, 3, 7, 'V', "ABBAGE", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 6);
    game = place_tiles(game, 5, 5, 'H', "BA Y", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 3);
    game = place_tiles(game, 5, 5, 'H', " E OP", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 3);
    game = place_tiles(game, 5, 6, 'H', "A BLE", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 4);
    game = place_tiles(game, 8, 5, 'H', "WOL FIESEAWOLF", &num_tiles_placed); // illegal move
    EXPECT_EQ(num_tiles_placed, 0);
    game = place_tiles(game, 5, 5, 'H', "R", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 1);
    game = place_tiles(game, 5, 5, 'H', "C", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 1);
    game = place_tiles(game, 5, 5, 'H', "J", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 1);
    game = place_tiles(game, 5, 5, 'V', "D", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 1);    
    game = place_tiles(game, 5, 5, 'V', "C", &num_tiles_placed); // illegal move
    EXPECT_EQ(num_tiles_placed, 0);  
    game = undo_place_tiles(game);
    game = undo_place_tiles(game);    
    game = place_tiles(game, 5, 5, 'V', "H", &num_tiles_placed);
    EXPECT_EQ(num_tiles_placed, 1);    
    game = place_tiles(game, 5, 5, 'V', "P", &num_tiles_placed); 
    EXPECT_EQ(num_tiles_placed, 1);  

    save_game_state(game, actual_filename);

    const char *expected_filename = "./tests/expected_outputs/multiple06.txt"; 
    char *expected_output = load_file(expected_filename);
    char *actual_output = load_file(actual_filename);
    EXPECT_STREQ(expected_output, actual_output);

    free(expected_output);
    free(actual_output);
    free_game_state(game);
}