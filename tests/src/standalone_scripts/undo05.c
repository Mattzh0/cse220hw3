#include "hw3.h"

int main(void) {
    const char *actual_filename = "./tests/actual_outputs/test_output.txt";
    int num_tiles_placed;
    GameState *game = initialize_game_state("./tests/boards/board2x2.txt");
    game = place_tiles(game, 0, 0, 'H', "CAT", &num_tiles_placed);
    game = place_tiles(game, 0, 3, 'H', "ASTROPHE", &num_tiles_placed);
    game = place_tiles(game, 0, 2 ,'H', " ASTROPHE", &num_tiles_placed);
    game = place_tiles(game, 1, 1 ,'V', "STRONAUT", &num_tiles_placed);
    game = undo_place_tiles(game);
    game = undo_place_tiles(game);
    game = place_tiles(game, 0, 0, 'H', "DOG", &num_tiles_placed);
    game = undo_place_tiles(game);
    save_game_state(game, actual_filename);
    free_game_state(game);
    return 0;
}
