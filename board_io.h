#ifndef BOARD_IO_H
#define BOARD_IO_H

#include <stdio.h>
#include <stdlib.h>
#include "chessboard.h"


char* position_to_string(int pos[]);
int* string_to_position(char pos[]);
char* get_input_position(char prompt[]);
void put_piece_prompt(int next, int board_state[][BOARD_SIZE], int last_put[]);


#endif
