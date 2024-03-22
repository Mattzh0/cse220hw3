#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#include "hw3.h" 

#define DEBUG(...) fprintf(stderr, "[          ] [ DEBUG ] "); fprintf(stderr, __VA_ARGS__); fprintf(stderr, " -- %s()\n", __func__)

void change_size(GameState *game, int r, int c);
int legal_word(char *word);

GameState *g;
FILE *words_file;
FILE *output_file;

GameState* initialize_game_state(const char *filename) {
    int file_height = 0;
    int file_width = 0;
    int file_length = 0;
    char ch;

    FILE *input_file = fopen(filename, "r");

    while ((ch = fgetc(input_file)) != EOF) {
        if (ch == '\n') {
            file_height++;
        } else {
            file_length++;
        }
    }
    rewind(input_file);
    file_width = (file_length / file_height);

    char **board_data = malloc(file_height * sizeof(char *));
    for (int i = 0; i < file_height; i++) {
        board_data[i] = malloc(file_width * sizeof(char));
    }

    int **height = calloc(file_height, sizeof(int *));
    for (int i = 0; i < file_height; i++) {
        height[i] = calloc(file_width, sizeof(int));
    }

    int row = 0, col = 0;
    while ((ch = fgetc(input_file)) != EOF) {
        if (ch == '\n') {
            row++;
            col = 0;
        } else {
            if (ch != '.') {
                height[row][col] = 1;
            }
            board_data[row][col] = ch;
            col++;
        }
    }
    fclose(input_file);


    g = malloc(sizeof(GameState));
    g->rows = file_height;
    g->columns = file_width;
    g->board = board_data;
    g->height = height;

    return g;
}

GameState* place_tiles(GameState *game, int row, int col, char direction, const char *tiles, int *num_tiles_placed) {
    int tiles_len = strlen(tiles);
    const char *tiles_ref = tiles;
    int place_count = 0;

    if ((row < 0) || (col < 0) || (row >= game->rows) || (col >= game->columns)) {
        return game;
    }

    char *built_word = malloc(64 * sizeof(char));
    int char_idx = 0;
    if (direction == 'H') {
        for (int i = col; i <= col + tiles_len - 1; i++) {
            if (i >= game->columns) {
                change_size(game, game->rows, i+1);
            }

            if (*tiles_ref == ' ') {
                built_word[char_idx++] = (game->board)[row][i];
                tiles_ref++;
                continue;
            }

            (game->board)[row][i] = *tiles_ref;
            built_word[char_idx++] = *tiles_ref;
            (game->height)[row][i]++;
            tiles_ref++;
            place_count++;

            if (game->height[row][i] > 5) {
                //implement undo later
                return game;
            }
        }
    }
    else if (direction == 'V') {
        for (int i = row; i <= row + tiles_len - 1; i++) {
            if (i >= game->rows) {
                change_size(game, i+1, game->columns);
            }

            if (*tiles_ref == ' ') {
                built_word[char_idx++] = (game->board)[i][col];
                tiles_ref++;
                continue;
            }
            
            (game->board)[i][col] = *tiles_ref;
            built_word[char_idx++] = *tiles_ref;
            (game->height)[i][col]++;
            tiles_ref++;
            place_count++;

            if (game->height[i][col] > 5) {
                //implement undo later
                return game;
            }
        }
    }
    else {
        return game;
    }
    built_word[char_idx] = '\0';

    if (!legal_word(built_word)) {
        //implement undo later
        return game;
    }

    /* printf("%s %d", built_word, strlen(built_word));

    printf("\n");

    for (int i = 0; i < game->rows; i++) {
        for (int j = 0; j < game->columns; j++) {
            printf("%c", game->board[i][j]);
        }
        printf("\n");
    }

    printf("\n");

    for (int i = 0; i < game->rows; i++) {
        for (int j = 0; j < game->columns; j++) {
            printf("%d", game->height[i][j]);
        }
        printf("\n");
    } */

    *num_tiles_placed = place_count;
    return game;
}

GameState* undo_place_tiles(GameState *game) {
    (void)game;
    return NULL;
}

void free_game_state(GameState *game) {
    (void)game;
}

void save_game_state(GameState *game, const char *filename) {
    output_file = fopen(filename, "w");

    for (int i = 0; i < game->rows; i++) {
        for (int j = 0; j < game->columns; j++) {
            fprintf(output_file, "%c", game->board[i][j]);
        }
        fprintf(output_file, "\n");
    }

    for (int i = 0; i < game->rows; i++) {
        for (int j = 0; j < game->columns; j++) {
            fprintf(output_file, "%d", game->height[i][j]);
        }
        fprintf(output_file, "\n");
    }

    fclose(output_file);
}

void change_size(GameState *game, int r, int c) {
    char **new_board = malloc(r * sizeof(char *));
    for (int i = 0; i < r; i++) {
        new_board[i] = malloc(c * sizeof(char));
        for (int j = 0; j < c; j++) {
            new_board[i][j] = '.';
        }
    }

    int **new_height = calloc(r, sizeof(int *));
    for (int i = 0; i < r; i++) {
        new_height[i] = calloc(c, sizeof(int));
    }

    for (int i = 0; i < game->rows; i++) {
        for (int j = 0; j < game->columns; j++) {
            new_board[i][j] = game->board[i][j];
        }
    }

    for (int i = 0; i < game->rows; i++) {
        for (int j = 0; j < game->columns; j++) {
            new_height[i][j] = game->height[i][j];
        }
    }

    for (int i = 0; i < game->rows; i++) {
        free(game->board[i]);
    }
    free(game->board);

    for (int i = 0; i < game->rows; i++) {
        free(game->height[i]);
    }
    free(game->height);

    game->rows = r;
    game->columns = c;
    game->board = new_board;
    game->height = new_height;
}

int legal_word(char *word) {
    words_file = fopen("./tests/words.txt", "r");
    //words_file = fopen("words.txt", "r");

    char *line = malloc(64 * sizeof(char));

    char *lower_word = malloc(strlen(word) + 1);
    for (int i = 0; word[i]; i++) {
        lower_word[i] = tolower(word[i]);
    }
    lower_word[strlen(word)] = '\0';

    while (fgets(line, 64, words_file)) {
        line[strcspn(line, "\n")] = '\0';

        for (int i = 0; line[i]; i++) {
            line[i] = tolower(line[i]);
        }

        if (strcmp(line, lower_word) == 0) {
            free(line);
            free(lower_word);
            fclose(words_file);
            return 1;
        }
    }
    free(line);
    free(lower_word);
    fclose(words_file);
    return 0;
}

/* int main(void) {
    int num = 0;
    GameState *game = initialize_game_state("board01.txt");
    place_tiles(game, 3, 2, 'H', "T Z E", &num);

    return 0;
} */