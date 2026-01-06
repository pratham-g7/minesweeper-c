#ifndef MAIN_H
#define MAIN_H

#include <stdbool.h>

extern char *code;             
extern int saved;                
extern const char *save_location; 


typedef struct {
    char ***board;  
    char ***ans;    
    int dim[2];    
} GameData;



int minesweeper_loop(char ***board, char ***ans, int dim[2], int bomb_count);


void start_game(void);


GameData* start(void);


void create_board(int dim[2], int ignore[2], int std, char ****board_out, char ****ans_out);
void display(char ***board, int dim[2]);
int valid_pos(int pos[2], int dim[2]);
int check_square(char ***board, char ***ans, int index[2], int bomb_count, int dim[2]);
char *reveal_square(int index[2], char ***board, char ***ans, char *rev, int dim[2]);
int check_win(int dim[2], int bomb_count);

#endif /* MAIN_H */
