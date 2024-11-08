#include "chessboard.h"

const int BOARD_SIZE = 15;
const int BLACK = 1;
const int WHITE = 2;


// Needed for `void draw_board`
int get_on_board_chars(int line, int column, int state, int last_put[]) {
    if (state == 0) {   // No chess piece in the spot
        if (line == 0) {
            if (column == 0) {
                wprintf(L"%lc", L'┌');
            }
            else if (column == BOARD_SIZE - 1) {
                wprintf(L"%lc", L'┐');
            }
            else {
                wprintf(L"%lc", L'┬');
            }
        }
        else if (line == BOARD_SIZE - 1) {
            if (column == 0) {
                wprintf(L"%lc", L'└');
            }
            else if (column == BOARD_SIZE - 1) {
                wprintf(L"%lc", L'┘');
            }
            else {
                wprintf(L"%lc", L'┴');
            }
        }
        else {
            if (column == 0) {
                wprintf(L"%lc", L'├');
            }
            else if (column == BOARD_SIZE - 1) {
                wprintf(L"%lc", L'┤');
            }
            else {
                wprintf(L"%lc", L'┼');
            }
        }
    }
    else if (state == WHITE) {
        if (last_put[0] == line && last_put[1] == column) {
            wprintf("\033[31m" L"%lc" "\033[0m", L'○');

        }
        else{
            wprintf(L"%lc", L'○');
        }
    }
    else if (state == BLACK) {
        if (last_put[0] == line && last_put[1] == column) {
            wprintf("\033[31m" L"%lc" "\033[0m", L'●');
        }
        else {
            wprintf(L"%lc", L'●');
        }
    }

    if (column != BOARD_SIZE - 1) {
        return L'─';
    }
    return L'\n';
}

// Draw chessboard
void draw_board(int board_state[][BOARD_SIZE], int last_put_position[]) {
    for (int i = 0; i < BOARD_SIZE; ++i) {         // Line number (by character)
        // Print Line number
        printf("%3d  ", BOARD_SIZE - i);
        for (int j = 0; j < BOARD_SIZE; ++j) {    // Column number (by character)
            wprintf(L"%lc", get_on_board_chars(i, j, board_state[i][j], last_put_position));
        }
    }
    printf("     ");
    for (int c = 'A'; c < 'A' + BOARD_SIZE; ++c) {
        printf("%c ", c);
    }
    printf("\n");
}

// Put BLACK or WHITE piece in `position`
void put_piece(int color, int position[], int board_state[][BOARD_SIZE], int last_put[]) {
    assert (color == BLACK || color == WHITE);

    board_state[position[0]][position[1]] = color;
    last_put[0] = position[0];
    last_put[1] = position[1];
}


