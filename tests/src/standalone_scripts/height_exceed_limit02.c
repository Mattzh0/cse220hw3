#include "hw3.h"

int main(void) {
    const char *actual_filename = "./tests/actual_outputs/test_output.txt";
    int num_tiles_placed;
    GameState *game = initialize_game_state("./tests/boards/board02.txt"); 
    game = place_tiles(game,0 , 0, 'V', "ARABLE", &num_tiles_placed);
    game = place_tiles(game,0 , 0, 'V', "DO", &num_tiles_placed);
    game = place_tiles(game,0 , 0, 'V', "EN", &num_tiles_placed);
    game = place_tiles(game,0 , 0, 'V', "LI", &num_tiles_placed);
    game = place_tiles(game,0 , 0, 'V', "ME", &num_tiles_placed);
    game = place_tiles(game,0 , 0, 'V', "ST", &num_tiles_placed);
    save_game_state(game, actual_filename);
    free_game_state(game);
    return 0;
}
