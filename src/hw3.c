#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#include "hw3.h" 

#define DEBUG(...) fprintf(stderr, "[          ] [ DEBUG ] "); fprintf(stderr, __VA_ARGS__); fprintf(stderr, " -- %s()\n", __func__)

void change_size(GameState *game, int r, int c);
int legal_word(char *word);
GameState *copy_game_state(GameState *game);

Stack* create_stack();
void push(Stack *stack, GameState *gameState);
GameState* pop(Stack *stack);
void free_stack(Stack *stack);

FILE *words_file;
FILE *output_file;
Stack* undoStack = NULL;

GameState* initialize_game_state(const char *filename) {
    int file_height = 0;
    int file_width = 0;
    int file_length = 0;
    char ch;
    
    undoStack = create_stack();

    GameState *g = malloc(sizeof(GameState));
    g->is_empty = 1;

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
                g->is_empty = 0;
                height[row][col] = 1;
            }
            board_data[row][col] = ch;
            col++;
        }
    }
    fclose(input_file);

    g->rows = file_height;
    g->columns = file_width;
    g->board = board_data;
    g->height = height;
    return g;
}

GameState* place_tiles(GameState *game, int row, int col, char direction, const char *tiles, int *num_tiles_placed) {
    *num_tiles_placed = 0;
    GameState *copy = copy_game_state(game);
    int tiles_len = strlen(tiles);
    const char *tiles_ref = tiles;
    int place_count = 0;
    int existing_tiles_covered = 0;
    int existing_tiles_used = 0;

    if ((row < 0) || (col < 0) || (row >= game->rows) || (col >= game->columns)) {
        free_game_state(copy);
        return game;
    }

    if (game->is_empty && tiles_len < 2) {
        free_game_state(game);
        return copy;
    }

    if (direction == 'H') {
        for (int i = col; i <= col + tiles_len - 1; i++) {
            if (i >= game->columns) {
                change_size(game, game->rows, i+1);
            }

            if (*tiles_ref == ' ') {
                existing_tiles_used++;
                tiles_ref++;
                continue;
            }

            if ((game->board)[row][i] == *tiles_ref) {
                free_game_state(game);
                return copy;
            }
            if ((game->board)[row][i] != '.') {
                existing_tiles_covered++;
            }
            (game->board)[row][i] = *tiles_ref;
            (game->height)[row][i]++;
            tiles_ref++;
            place_count++;

            if (game->height[row][i] > 5) {
                free_game_state(game);
                return copy;
            }
        }
    }
    else if (direction == 'V') {
        for (int i = row; i <= row + tiles_len - 1; i++) {
            if (i >= game->rows) {
                change_size(game, i+1, game->columns);
            }

            if (*tiles_ref == ' ') {
                existing_tiles_used++;
                tiles_ref++;
                continue;
            }

            if ((game->board)[i][col] == *tiles_ref) {
                free_game_state(game);
                return(copy);
            }
            if ((game->board)[i][col] != '.') {
                existing_tiles_covered++;
            }
            (game->board)[i][col] = *tiles_ref;
            (game->height)[i][col]++;
            tiles_ref++;
            place_count++;

            if (game->height[i][col] > 5) {
                free_game_state(game);
                return copy;
            }
        }
    }
    else {
        free_game_state(copy);
        return game;
    }

    char *built_word_horizontal = malloc(256 * sizeof(char));
    char *built_word_vertical = malloc(256 * sizeof(char));
    memset(built_word_horizontal, '\0', 256);
    memset(built_word_vertical, '\0', 256);
    int char_idx_horizontal = 0;
    int char_idx_vertical = 0;
    if (direction == 'H') {
        int start = col;
        while (start > 0 && game->board[row][start - 1] != '.') {
            start--;
        }

        int end = col + tiles_len - 1;
        while (end < game->columns - 1 && game->board[row][end + 1] != '.') {
            end++;
        }

        strncpy(built_word_horizontal, &game->board[row][start], end - start + 1);
        built_word_horizontal[end - start + 1] = '\0';

        if (!legal_word(built_word_horizontal)) {
            free_game_state(game);
            free(built_word_horizontal);
            free(built_word_vertical);
            return copy;
        }

        for (int i = col; i <= col + tiles_len - 1; i++) {
            if (game->board[row][i] == '.') {
                continue;
            }

            int s = row;
            while (s > 0 && game->board[s - 1][i] != '.') {
                s--;
            }

            int e = row;
            while (e < game->rows - 1 && game->board[e + 1][i] != '.') {
                e++;
            }

            if (e - s > 0) {
                char_idx_vertical = 0;
                for (int j = s; j <= e; j++) {
                    built_word_vertical[char_idx_vertical++] = game->board[j][i];
                }
                built_word_vertical[char_idx_vertical] = '\0';

                if (!legal_word(built_word_vertical)) {
                    free_game_state(game);
                    free(built_word_horizontal);
                    free(built_word_vertical);
                    return copy;
                }
            }
        }
    } 
    else if (direction == 'V') {
        int start = row;
        while (start > 0 && game->board[start - 1][col] != '.') {
            start--;
        }

        int end = row + tiles_len - 1;
        while (end < game->rows - 1 && game->board[end + 1][col] != '.') {
            end++;
        }

        for (int i = start; i <= end; i++) {
            built_word_vertical[char_idx_vertical++] = game->board[i][col];
        }
        built_word_vertical[char_idx_vertical] = '\0';

        if (!legal_word(built_word_vertical)) {
            free_game_state(game);
            free(built_word_horizontal);
            free(built_word_vertical);
            return copy;
        }

        for (int i = row; i <= row + tiles_len - 1; i++) {
            if (game->board[i][col] == '.') {
                continue;
            }

            int s = col;
            while (s > 0 && game->board[i][s - 1] != '.') {
                s--;
            }

            int e = col;
            while (e < game->columns - 1 && game->board[i][e + 1] != '.') {
                e++;
            }

            if (e - s > 0) {
                char_idx_horizontal = 0;
                for (int j = s; j <= e; j++) {
                    built_word_horizontal[char_idx_horizontal++] = game->board[i][j];
                }
                built_word_horizontal[char_idx_horizontal] = '\0';

                if (!legal_word(built_word_horizontal)) {
                    free_game_state(game);
                    free(built_word_horizontal);
                    free(built_word_vertical);
                    return copy;
                }
            }
        }
    }
    
    if (built_word_horizontal) {
        if (((int)strlen(built_word_horizontal) == place_count) && ((int)strlen(built_word_horizontal) == existing_tiles_covered)) {
            if (!legal_word(built_word_vertical)) {
                free_game_state(game);
                free(built_word_horizontal);
                free(built_word_vertical);
                return copy;
            }
        }
        if (!game->is_empty && ((int)strlen(built_word_horizontal) == place_count) && existing_tiles_covered == 0 && existing_tiles_used == 0) {
            if (!legal_word(built_word_vertical)) {
                free_game_state(game);
                free(built_word_horizontal);
                free(built_word_vertical);
                return copy;
            }
        }
    }
    if (built_word_vertical) {
        if (((int)strlen(built_word_vertical) == place_count) && ((int)strlen(built_word_vertical) == existing_tiles_covered)) {
            if (!legal_word(built_word_horizontal)) {
                free_game_state(game);
                free(built_word_horizontal);
                free(built_word_vertical);
                return copy;
            }
        }
        if (!game->is_empty && ((int)strlen(built_word_vertical) == place_count) && existing_tiles_covered == 0 && existing_tiles_used == 0) {
            if (!legal_word(built_word_horizontal)) {
                free_game_state(game);
                free(built_word_horizontal);
                free(built_word_vertical);
                return copy;
            }
        }
    }
    
    push(undoStack, copy);
    game->is_empty = 0;
    *num_tiles_placed = place_count;
    free(built_word_horizontal);
    free(built_word_vertical);

    return game;
}

GameState* undo_place_tiles(GameState *game) {
    if (undoStack == NULL) {
        undoStack = create_stack();
    }
    GameState *prevGameState = pop(undoStack);
    if (prevGameState == NULL) {
        return game; 
    }
    free_game_state(game);

    return prevGameState;
}

void free_game_state(GameState *game) {
    for (int i = 0; i < game->rows; i++) {
        free(game->board[i]);
        free(game->height[i]);
    }
    free(game->board);
    free(game->height);
    free(game);
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

GameState *copy_game_state(GameState *game) {
    GameState *copy = malloc(sizeof(GameState));
    copy->rows = game->rows;
    copy->columns = game->columns;
    copy->board = malloc(copy->rows * sizeof(char*));
    copy->height = malloc(copy->rows * sizeof(int*));
    copy->is_empty = game->is_empty;
    for (int i = 0; i < copy->rows; i++) {
        copy->board[i] = malloc(copy->columns * sizeof(char));
        memcpy(copy->board[i], game->board[i], copy->columns * sizeof(char));
        copy->height[i] = malloc(copy->columns * sizeof(int));
        memcpy(copy->height[i], game->height[i], copy->columns * sizeof(int));
    }
    return copy;
}

Stack* create_stack() {
    Stack *stack = malloc(sizeof(Stack));
    stack->top = NULL;
    return stack;
}

void push(Stack *stack, GameState *gameState) {
    StackNode *newNode = malloc(sizeof(StackNode));
    newNode->gameState = gameState;
    newNode->next = stack->top;
    stack->top = newNode;
}

GameState* pop(Stack *stack) {
    if (stack->top == NULL) {
        return NULL;
    }
    StackNode *temp = stack->top;
    GameState *gameState = temp->gameState;
    stack->top = stack->top->next;
    free(temp);
    return gameState;
}

void free_stack(Stack *stack) {
    while (stack->top != NULL) {
        pop(stack);
    }
    free(stack);
}