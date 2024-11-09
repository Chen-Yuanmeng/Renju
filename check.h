#include "chessboard.h"

int check(int board_state[][BOARD_SIZE], int last_put[]);
int check_win(int board_state[][BOARD_SIZE], int last_put[]);
int check_forbidden_move(int board_state[][BOARD_SIZE], int last_put[]);
int check_full_board(int board_state[][BOARD_SIZE], int last_put[]);
