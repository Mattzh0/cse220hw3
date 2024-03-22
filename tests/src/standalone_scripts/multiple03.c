#include "hw3.h"

int main(void) {
    const char *actual_filename = "./tests/actual_outputs/test_output.txt";
    int num_tiles_placed;
	GameState *game = initialize_game_state("./tests/boards/board01.txt"); 
    game = place_tiles(game, 2, 3, 'V', "T P", &num_tiles_placed);
    game = place_tiles(game, 2, 5, 'V', "P T", &num_tiles_placed);
    save_game_state(game, actual_filename);
    free_game_state(game);
    return 0;
}
