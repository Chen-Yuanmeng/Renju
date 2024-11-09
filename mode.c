// This file defines multiple modes in Renju program:

#include "mode.h"

// Man-man combat
void man_man() {
    // Initialize board state:
    // 0: No piece whatsoever
    // 1: White piece `WHITE`
    // 2: Black piece `BLACK`
    int board_state[BOARD_SIZE][BOARD_SIZE] = {};

    // Initialize position last put (default -1, -1)
    // All positions are (line, column) from 0 up.
    // Example: A15 (0, 0) | O15 (0, 14) | 
    int last_put[2] = {-1, -1};
    
    // Put first piece at H8
    int first_position[2] = {7, 7};
    put_piece(BLACK, first_position, board_state, last_put);
    draw_board(board_state, last_put);
    printf("The first Black piece has been put at H8 for you.\nPress any key to continue...");
    system("pause > nul");
    system("cls");
    draw_board(board_state, last_put);

    // Loop until status becomes true
    int status = 0;
    int next = WHITE;
    while (!status) {
        put_piece_prompt(next, board_state, last_put);
        next = (next == BLACK) ? WHITE : BLACK;
        system("cls");
        draw_board(board_state, last_put);
        status = check(board_state, last_put, next);
        check_prompt(status);
    };
}

// Man-machine combat
void man_machine() {
    // Initialize board state:
    // 0: No piece whatsoever
    // 1: White piece
    // 2: Black piece
    int board_state[BOARD_SIZE][BOARD_SIZE] = {};

    // Initialize position last put (default -1, -1)
    // All positions are (line, column) from 0 up.
    // Example: A15 (0, 0) | O15 (0, 14) | 
    int last_put[2] = {-1, -1};                     
    printf("To be developed...\n");
    system("pause");

}

// Machine-man combat
void machine_man() {
    // Initialize board state:
    // 0: No piece whatsoever
    // 1: White piece
    // 2: Black piece
    int board_state[BOARD_SIZE][BOARD_SIZE] = {};

    // Initialize position last put (default -1, -1)
    // All positions are (line, column) from 0 up.
    // Example: A15 (0, 0) | O15 (0, 14) | 
    int last_put[2] = {-1, -1};                     
    printf("To be developed...\n");
    system("pause");

}

// Machine-machine combat (only for training/testing purposes)
void machine_machine() {
    // Initialize board state:
    // 0: No piece whatsoever
    // 1: White piece
    // 2: Black piece
    int board_state[BOARD_SIZE][BOARD_SIZE] = {};

    // Initialize position last put (default -1, -1)
    // All positions are (line, column) from 0 up.
    // Example: A15 (0, 0) | O15 (0, 14) | 
    int last_put[2] = {-1, -1};                     
    printf("To be developed...\n");
    system("pause");

}
