#ifndef MAIN_H
#define MAIN_H

#include <stdbool.h>

/* ---------- Global variables ---------- */
extern char *code;                // current save code
extern int saved;                 // flag if game is saved
extern const char *save_location; // save file path

/* ---------- Structs ---------- */
/* Represents loaded or new game data */
typedef struct {
    char ***board;  // 2D board array
    char ***ans;    // 2D answer array (bombs / numbers)
    int dim[2];     // dimensions: dim[0] = rows, dim[1] = cols
} GameData;

/* ---------- Function prototypes ---------- */

/* Main Minesweeper loop for one turn */
int minesweeper_loop(char ***board, char ***ans, int dim[2], int bomb_count);

/* Entry point to start/load the game */
void start_game(void);

/* Start function that returns saved or new game */
GameData* start(void);

/* Minesweeper board functions */
void create_board(int dim[2], int ignore[2], int std, char ****board_out, char ****ans_out);
void display(char ***board, int dim[2]);
int valid_pos(int pos[2], int dim[2]);
int check_square(char ***board, char ***ans, int index[2], int bomb_count, int dim[2]);
char *reveal_square(int index[2], char ***board, char ***ans, char *rev, int dim[2]);
int check_win(int dim[2], int bomb_count);

#endif /* MAIN_H */
