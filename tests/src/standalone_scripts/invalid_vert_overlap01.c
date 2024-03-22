#include "hw3.h"

int main(void) {
    const char *actual_filename = "./tests/actual_outputs/test_output.txt";
    int num_tiles_placed;
	GameState *game = initialize_game_state("./tests/boards/board04.txt");
    game = place_tiles(game, 4, 12, 'V', "DINGO", &num_tiles_placed);
    save_game_state(game, actual_filename);
    free_game_state(game);
    return 0;
}
