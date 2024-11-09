#ifndef __CHECK_H
#define __CHECK_H

#include <string.h>
#include "chessboard.h"

int check(int board_state[][BOARD_SIZE], int last_put[], int next);
int check_win(int board_state[][BOARD_SIZE], int last_put[], int next);
int check_forbidden_move(int board_state[][BOARD_SIZE], int last_put[], int next);
int check_full_board(int board_state[][BOARD_SIZE], int last_put[]);
int is_forbidden_move(int board_state[][BOARD_SIZE], int x_row, int y_column);
int check_double_three(int board_state[][BOARD_SIZE], int x_row, int y_column);
int check_double_four(int board_state[][BOARD_SIZE], int x_row, int y_column);
int check_overline(int board_state[][BOARD_SIZE], int x_row, int y_column);

#endif
