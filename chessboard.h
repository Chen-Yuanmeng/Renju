#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <stdio.h>
#include <wchar.h>
#include <assert.h>
#include <time.h>

extern const int BOARD_SIZE;
extern const int BLACK;
extern const int WHITE;

int get_on_board_chars(int line, int column, int state, int last_put[]);

void draw_board(int board_state[][BOARD_SIZE], int last_put_position[]);

void put_piece(int color, int position[], int board_state[][BOARD_SIZE], int last_put[]);


#endif
