#include "hw3.h"

int main(void) {
    const char *actual_filename = "./tests/actual_outputs/test_output.txt";
    int num_tiles_placed;
	GameState *game = initialize_game_state("./tests/boards/board2x2.txt"); 
    game = place_tiles(game, 0, 0, 'V', "ABDOMINOPOSTERIOR", &num_tiles_placed);
    game = place_tiles(game, 2, 0, 'H', " INER", &num_tiles_placed);
    game = place_tiles(game, 2, 4, 'H', "URIC", &num_tiles_placed);
    game = place_tiles(game, 1, 5, 'H', "OH", &num_tiles_placed);
    game = place_tiles(game, 3, 7, 'V', "ARE", &num_tiles_placed);
    game = place_tiles(game, 5, 4, 'H', "TAK", &num_tiles_placed);
    game = place_tiles(game, 5, 4, 'H', "B   D", &num_tiles_placed);
    game = undo_place_tiles(game);
    game = undo_place_tiles(game);
    game = undo_place_tiles(game);
    game = place_tiles(game, 3, 7, 'V', "ABBAGE", &num_tiles_placed);
    game = place_tiles(game, 5, 5, 'H', "BA Y", &num_tiles_placed);
    game = place_tiles(game, 5, 5, 'H', " E OP", &num_tiles_placed);
    game = place_tiles(game, 5, 6, 'H', "A BLE", &num_tiles_placed);
    game = place_tiles(game, 8, 5, 'H', "WOL FIESEAWOLF", &num_tiles_placed); // illegal move
    game = place_tiles(game, 5, 5, 'H', "R", &num_tiles_placed);
    game = place_tiles(game, 5, 5, 'H', "C", &num_tiles_placed);
    game = place_tiles(game, 5, 5, 'H', "J", &num_tiles_placed);
    game = place_tiles(game, 5, 5, 'V', "D", &num_tiles_placed);
    game = place_tiles(game, 5, 5, 'V', "C", &num_tiles_placed); // illegal move
    game = undo_place_tiles(game);
    game = undo_place_tiles(game);    
    game = place_tiles(game, 5, 5, 'V', "H", &num_tiles_placed);
    game = place_tiles(game, 5, 5, 'V', "P", &num_tiles_placed); 
    save_game_state(game, actual_filename);
    free_game_state(game);
    return 0;
}
