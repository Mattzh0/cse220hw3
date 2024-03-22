#include "hw3.h"

int main(void) {
    const char *actual_filename = "./tests/actual_outputs/test_output.txt";
    int num_tiles_placed;
	GameState *game = initialize_game_state("./tests/boards/board02.txt");
    game = place_tiles(game, 0, 0, 'H', "C", &num_tiles_placed);
    game = place_tiles(game, 0, 0, 'H', "CAT", &num_tiles_placed);
    game = place_tiles(game, 0, 1, 'H', "DOG", &num_tiles_placed);
    game = place_tiles(game, 0, 0, 'V', " AR", &num_tiles_placed);
    game = place_tiles(game, 0, 0, 'V', "   NIVAL", &num_tiles_placed);
    game = place_tiles(game, 0, 0, 'H', "   ABASES", &num_tiles_placed);
    game = place_tiles(game, 0, 7, 'V', " ARPHONE", &num_tiles_placed);
    game = place_tiles(game, 7, 0, 'H', " ACERAT ", &num_tiles_placed);
    game = undo_place_tiles(game);
    game = place_tiles(game, 7, 0, 'H', " IGHTKE PER", &num_tiles_placed);
    game = place_tiles(game, 0, 0, 'H', "  BDRIV R", &num_tiles_placed);
    save_game_state(game, actual_filename);
    free_game_state(game);
    return 0;
}
