#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"


/* ---------- Globals ---------- */
char *code = NULL;
int saved = 0;
const char *save_location = "minesweeper_saves\\minesweeper.dat";

/* ---------- start() ---------- */
GameData* start(void) {
    // start new game
    return NULL;
}
void start_game(void) {
    int dim[2];
    int ignore[2];
    char ***board = NULL;
    char ***ans = NULL;
    int bomb_count;

    /* Start / load game */
    GameData *loaded_data = start();  // NULL or saved game data

    if (!loaded_data) {
        /* difficulty + board creation */
        printf("Enter number of rows: ");
        scanf("%d", &dim[0]);
        printf("Enter number of columns: ");
        scanf("%d", &dim[1]);
        int bomb_count = (dim[0] * dim[1]) / 5; // simple bomb count
        create_board(dim, NULL, 0, &board, &ans);
    } else {
        /* Load saved game */
        board = loaded_data->board;
        ans = loaded_data->ans;
        dim[0] = loaded_data->dim[0];
        dim[1] = loaded_data->dim[1];
    }

    /* Count bombs */
    bomb_count = 0;
    for (int i = 0; i < dim[0]; i++)
        for (int j = 0; j < dim[1]; j++)
            if (strcmp(ans[i][j], "X ") == 0) bomb_count++;

    /* ---------- Main Game Loop ---------- */
    while (1) {
        display(board, dim);
        if (!minesweeper_loop(board, ans, dim, bomb_count)) {
            printf("Game Over! Press Enter to exit...");
            getchar(); getchar();
            break;
        }
    }
}

/* ---------- minesweeper_loop() ---------- */
int minesweeper_loop(char ***board, char ***ans, int dim[2], int bomb_count) {
    int row, col;
    printf("Enter row and column (1-based): ");
    if (scanf("%d %d", &row, &col) != 2) {
        printf("Invalid input. Please enter two numbers.\n");
        while (getchar() != '\n'); // clear buffer
        return 1;
    }
    row--; col--; // convert to 0-based
    int index[2] = {row, col};
    if (!valid_pos(index, dim)) {
        printf("Invalid position.\n");
        return 1;
    }
    char *val = reveal_square(index, board, ans, NULL, dim);
    if (strcmp(val, "X ") == 0) {
        // Reveal all bombs
        for (int i = 0; i < dim[0]; i++) {
            for (int j = 0; j < dim[1]; j++) {
                if (strcmp(ans[i][j], "X ") == 0) {
                    board[i][j] = ans[i][j];
                }
            }
        }
        display(board, dim);
        printf("You hit a bomb! Game over.\n");
        return 0;
    }
    if (check_win(dim, bomb_count)) {
        display(board, dim);
        printf("Congratulations! You win!\n");
        return 0;
    }
    return 1;
}
int main(void) {
    start_game();
    return 0;
}
