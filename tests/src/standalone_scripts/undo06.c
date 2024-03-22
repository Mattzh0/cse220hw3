#include "hw3.h"

int main(void) {
    const char *actual_filename = "./tests/actual_outputs/test_output.txt";
    int num_tiles_placed;
    GameState *game = initialize_game_state("./tests/boards/board06.txt");
    game = undo_place_tiles(game);
    game = place_tiles(game, 8, 5, 'V', "SOME", &num_tiles_placed);
    game = place_tiles(game, 9, 17, 'V', "ABBAGE", &num_tiles_placed);
    game = place_tiles(game, 0, 0, 'H', "CAT", &num_tiles_placed);
    game = place_tiles(game, 8, 5, 'V', "SOME", &num_tiles_placed);
    game = place_tiles(game, 10, 5, 'H', " ANGANOCOLUM ITE", &num_tiles_placed);
    game = place_tiles(game, 10, 5, 'H', "HOME", &num_tiles_placed);
    game = undo_place_tiles(game);
    game = undo_place_tiles(game);
    game = undo_place_tiles(game);
    save_game_state(game, actual_filename);
    free_game_state(game);
    return 0;
}
