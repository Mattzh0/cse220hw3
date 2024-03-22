#include "hw3.h"

int main(void) {
    const char *actual_filename = "./tests/actual_outputs/test_output.txt";
    GameState *game = initialize_game_state("./tests/boards/board09.txt"); 
    save_game_state(game, actual_filename);
    free_game_state(game);
    return 0;
}
