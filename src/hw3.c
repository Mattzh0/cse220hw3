#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#include "hw3.h" 

#define DEBUG(...) fprintf(stderr, "[          ] [ DEBUG ] "); fprintf(stderr, __VA_ARGS__); fprintf(stderr, " -- %s()\n", __func__)

GameState* initialize_game_state(const char *filename) {
    (void)filename;
    return NULL;
}

GameState* place_tiles(GameState *game, int row, int col, char direction, const char *tiles, int *num_tiles_placed) {
    (void)game;
    (void)row;
    (void)col;
    (void)direction;
    (void)tiles;
    (void)num_tiles_placed;
    return NULL;
}

GameState* undo_place_tiles(GameState *game) {
    (void)game;
    return NULL;
}

void free_game_state(GameState *game) {
    (void)game;
}

void save_game_state(GameState *game, const char *filename) {
    (void)game;
    (void)filename;
}
