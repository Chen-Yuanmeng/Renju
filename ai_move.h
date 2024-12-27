#ifndef __AI_MOVE_H
#define __AI_MOVE_H

#include "chessboard.h"
#include "hashtable.h"
#include "evaluate.h"
#include <limits.h>
#include "check.h"
#include "board_io.h"

#define INFINITY 2000000
#define NEG_INFINITY -2000000
#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

#define TOTAL_DEPTH 4

typedef struct _move_t {
    Position pos;
    int score_used;
} Move_t;

void initialize();
void push_move(Position pos, Pair scores, int player);
Move pop_move();
Position move(int board_state[][BOARD_SIZE], int player, int role_computer);
void AI_put_piece(int color, Position pos, int board_state[][BOARD_SIZE], int role_computer);
void AI_remove_piece(int board_state[][BOARD_SIZE], int role_computer);
Move_t alpha_beta(int board_state[][BOARD_SIZE], int depth, int alpha, int beta, int player, int role_computer);
int find_available_moves(int board_state[][BOARD_SIZE], int player, Position* available_moves);
void print_counts();

#endif
