#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"


char *code = NULL;
int saved = 0;
const char *save_location = "minesweeper_saves\\minesweeper.dat";

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


    GameData *loaded_data = start();  

    if (!loaded_data) {
   
        printf("Enter number of rows: ");
        scanf("%d", &dim[0]);
        printf("Enter number of columns: ");
        scanf("%d", &dim[1]);
        int bomb_count = (dim[0] * dim[1]) / 5; 
        create_board(dim, NULL, 0, &board, &ans);
    } else {
 
        board = loaded_data->board;
        ans = loaded_data->ans;
        dim[0] = loaded_data->dim[0];
        dim[1] = loaded_data->dim[1];
    }

    bomb_count = 0;
    for (int i = 0; i < dim[0]; i++)
        for (int j = 0; j < dim[1]; j++)
            if (strcmp(ans[i][j], "X ") == 0) bomb_count++;

    while (1) {
        display(board, dim);
        if (!minesweeper_loop(board, ans, dim, bomb_count)) {
            printf("Game Over! Press Enter to exit...");
            getchar(); getchar();
            break;
        }
    }
}

int minesweeper_loop(char ***board, char ***ans, int dim[2], int bomb_count) {
    int row, col;
    printf("Enter row and column (1-based): ");
    if (scanf("%d %d", &row, &col) != 2) {
        printf("Invalid input. Please enter two numbers.\n");
        while (getchar() != '\n');
        return 1;
    }
    row--; col--;
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
