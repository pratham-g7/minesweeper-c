#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <stdbool.h>

/* ---------- External black boxes ---------- */
void prints(const char *text);

/* load_data:
   returns 1 if exists, 0 otherwise
   out_data is filled on success
*/
bool load_data(const char *path, const char *code, void **out_data);

/* ---------- Constants ---------- */
#define MAX_FINISHED 1000

/* ---------- Globals ---------- */
extern int finished_count;
extern int finished[MAX_FINISHED][2];

/* ---------- Core functions ---------- */
int valid_pos(int pos[2], int dim[2]);

char ***alloc_board(int rows, int cols);

char ***apply_point_check(char ***board, int dim[2]);

void create_board(
    int dim[2],
    int ignore[2],
    int std,
    char ****grid_out,
    char ****ans_out
);

void display(char ***g, int dim[2]);

int get_pts(char ***board, int dim[2]);

void flood_fill(
    char ***board,
    char ***ans,
    int loc[2],
    int dim[2]
);

char *reveal_square(
    int index[2],
    char ***board,
    char ***ans,
    char *rev,
    int dim[2]
);

int check_win(int dim[2], int bomb_count);

#endif /* MINESWEEPER_H */
