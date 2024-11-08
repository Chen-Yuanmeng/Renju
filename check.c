#include "check.h"

// Check entrance function: start check of all things
// return `int`: 0b000 - passed check; others - failed check
int check(int board_state[][BOARD_SIZE], int last_put[]) {
    return (
        check_win(board_state, last_put) + 
        check_prohibit_move(board_state, last_put) + 
        check_full_board(board_state, last_put)
    );
}

// Check win function: check if anyone wins
// return `int`: 0b0 - passed check; 0b1 - failed check
int check_win(int board_state[][BOARD_SIZE], int last_put[]) {

}

// Check prohibit function: check if Black has performed prohibited moves
// return `int`: 0b00 - passed check; 0b10 - failed check
int check_prohibit_move(int board_state[][BOARD_SIZE], int last_put[]) {

}

// Check full function: check if board is full
// return `int`: 0b000 - not full; 0b100 - full
int check_full_board(int board_state[][BOARD_SIZE], int last_put[]) {

}

