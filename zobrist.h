#ifndef __ZOBRIST_H
#define __ZOBRIST_H

#include "chessboard.h"
#include "xorshift.h"

void initializeZobrist();
unsigned long long computeZobristHash(int board[BOARD_SIZE][BOARD_SIZE]);
unsigned long long updateZobristHash(unsigned long long currentHash, int oldState, int newState, Position pos);

#endif