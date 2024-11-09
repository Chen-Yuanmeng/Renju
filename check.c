#include "check.h"

// Check entrance function: start check of all things
// return `int`:
//     0000 - passed check;
//     others - failed check
int check(int board_state[][BOARD_SIZE], int last_put[]) {
    // return (
    //     check_win(board_state, last_put) + 
    //     check_forbidden_move(board_state, last_put) + 
    //     check_full_board(board_state, last_put)
    // );
    return 0;
}

// Check win function: check if anyone wins
// return `int`:
//     00 - Nobody wins;
//     01 - Black wins;
//     02 - White wins;
int check_win(int board_state[][BOARD_SIZE], int last_put[]) {

}

// Check forbidden function: check if Black has performed forbidden moves
// return `int`:
//     000 - No forbidden moves;
//     010 - Black has forbidden moves;
int check_forbidden_move(int board_state[][BOARD_SIZE], int last_put[]) {

}

// Check full function: check if board is full
// return `int`:
//     0000 - not full;
//     0100 - full
int check_full_board(int board_state[][BOARD_SIZE], int last_put[]) {

}

