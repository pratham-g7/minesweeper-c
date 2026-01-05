#include "minesweeper_tools.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* ---------- Globals ---------- */
int finished_count = 0;
int finished[MAX_FINISHED][2];

/* ---------- Internal helpers ---------- */

static int in_finished(int x, int y) {
    for (int i = 0; i < finished_count; i++)
        if (finished[i][0] == x && finished[i][1] == y)
            return 1;
    return 0;
}

static void add_finished(int x, int y) {
    if (!in_finished(x, y) && finished_count < MAX_FINISHED) {
        finished[finished_count][0] = x;
        finished[finished_count][1] = y;
        finished_count++;
    }
}

/* ---------- valid_pos ---------- */

int valid_pos(int pos[2], int dim[2]) {
    return pos[0] >= 0 && pos[1] >= 0 &&
           pos[0] < dim[0] && pos[1] < dim[1];
}

/* ---------- Board allocation ---------- */

char ***alloc_board(int rows, int cols) {
    char ***b = malloc(rows * sizeof(char **));
    for (int i = 0; i < rows; i++) {
        b[i] = malloc(cols * sizeof(char *));
        for (int j = 0; j < cols; j++)
            b[i][j] = strdup("# ");
    }
    return b;
}

/* ---------- apply_point_check ---------- */

char ***apply_point_check(char ***board, int dim[2]) {
    char ***newb = alloc_board(dim[0], dim[1]);

    for (int i = 0; i < dim[0]; i++) {
        for (int j = 0; j < dim[1]; j++) {
            if (strcmp(board[i][j], "X") != 0) {
                int count = 0;
                for (int dx = -1; dx <= 1; dx++) {
                    for (int dy = -1; dy <= 1; dy++) {
                        int nx = i + dx, ny = j + dy;
                        if (nx >= 0 && ny >= 0 &&
                            nx < dim[0] && ny < dim[1] &&
                            strcmp(board[nx][ny], "X") == 0)
                            count++;
                    }
                }
                char buf[4];
                sprintf(buf, "%d ", count);
                newb[i][j] = strdup(buf);
            } else {
                newb[i][j] = strdup("X ");
            }
        }
    }
    return newb;
}

/* ---------- create_board ---------- */

void create_board(
    int dim[2],
    int ignore[2],
    int std,
    char ****grid_out,
    char ****ans_out
) {
    *grid_out = alloc_board(dim[0], dim[1]);

    if (std) {
        *ans_out = NULL;
        return;
    }

    srand((unsigned)time(NULL));

    char ***raw = alloc_board(dim[0], dim[1]);

    for (int i = 0; i < dim[0]; i++) {
        for (int j = 0; j < dim[1]; j++) {
            raw[i][j] =
                (rand() % 5 == 0) ? strdup("X") : strdup("$ ");
        }
    }

    if (ignore) {
        raw[ignore[0] - 1][ignore[1] - 1] = strdup("$ ");
    }

    *ans_out = apply_point_check(raw, dim);
}

/* ---------- display ---------- */

void display(char ***g, int dim[2]) {
    printf("  ");
    for (int i = 1; i <= dim[1]; i++)
        printf("%2d", i);
    printf("\n");

    for (int i = 0; i < dim[0]; i++) {
        printf("%2d|", i + 1);
        for (int j = 0; j < dim[1]; j++)
            printf("%s", g[i][j]);
        printf("|\n");
    }
}

/* ---------- get_pts ---------- */

int get_pts(char ***board, int dim[2]) {
    int sum = 0;
    for (int i = 0; i < dim[0]; i++) {
        for (int j = 0; j < dim[1]; j++) {
            if (strcmp(board[i][j], "X ") &&
                strcmp(board[i][j], "# "))
                sum += atoi(board[i][j]);
        }
    }
    return sum;
}

/* ---------- flood_fill ---------- */

void flood_fill(
    char ***board,
    char ***ans,
    int loc[2],
    int dim[2]
) {
    int x = loc[0], y = loc[1];
    if (in_finished(x, y)) return;

    add_finished(x, y);
    board[x][y] = ans[x][y];

    if (strcmp(ans[x][y], "0 ") == 0) {
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (!dx && !dy) continue;
                int nx = x + dx, ny = y + dy;
                if (nx >= 0 && ny >= 0 &&
                    nx < dim[0] && ny < dim[1]) {
                    int nloc[2] = {nx, ny};
                    flood_fill(board, ans, nloc, dim);
                }
            }
        }
    }
}

/* ---------- reveal_square ---------- */

char *reveal_square(
    int index[2],
    char ***board,
    char ***ans,
    char *rev,
    int dim[2]
) {
    char *val = rev ? rev : ans[index[0]][index[1]];
    board[index[0]][index[1]] = val;

    if (strcmp(val, "0 ") == 0)
        flood_fill(board, ans, index, dim);
    else
        add_finished(index[0], index[1]);

    return val;
}

/* ---------- check_win ---------- */

int check_win(int dim[2], int bomb_count) {
    return finished_count ==
           (dim[0] * dim[1] - bomb_count);
}
