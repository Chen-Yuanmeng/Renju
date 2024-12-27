#ifndef __BOARD_IO_H
#define __BOARD_IO_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "chessboard.h"
#include "ai_move.h"

char* position_to_string(int pos[]);
int* string_to_position(char pos[]);
char* get_input_position(char prompt[]);
void put_piece_prompt(int next, int board_state[][BOARD_SIZE], int last_put[]);
void check_prompt(int retval);

#endif
