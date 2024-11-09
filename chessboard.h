#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <stdio.h>
#include <wchar.h>
#include <assert.h>
#include <time.h>

#define BOARD_SIZE 15
#define BLACK 1
#define WHITE 2

int get_on_board_chars(int line, int column, int state, int last_put[]);

void draw_board(int board_state[][BOARD_SIZE], int last_put_position[]);

void put_piece(int color, int position[], int board_state[][BOARD_SIZE], int last_put[]);


#endif
