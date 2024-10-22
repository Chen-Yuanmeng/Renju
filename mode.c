// This file defines multiple modes in GoBang program:

#include "mode.h"
#include "chessboard.h"

// Man-man combat
void man_man() {
    // Initialize board state:
    // 0: No space whatsoever
    // 1: White piece `WHITE`
    // 2: Black piece `BLACK`
    int board_state[BOARD_SIZE][BOARD_SIZE] = {};

    // Initialize position last put (default -1, -1)
    // All positions are (line, column) from 0 up.
    // Example: A15 (0, 0) | O15 (0, 14) | 
    int last_put[2] = {-1, -1};
    
    
    // For testing purposes:
    // srand(time(NULL));
    // for (int i = 0; i < BOARD_SIZE; ++i) {
    //     for (int j = 0; j < BOARD_SIZE; ++j) {
    //         board_state[i][j] = rand() % 3;
    //         last_put[0] = i;
    //         last_put[1] = j;
    //     }
    // }


    // draw_board(board_state, last_put);


    // for (int i = 0; i < 10; ++i) {
    //     char* new_pos_str = get_input_position("\nPlease input position: ");
    //     int* new_pos = string_to_position(new_pos_str);
    //     printf("\n\nPiece: %s", new_pos_str);
    //     if (rand() % 2) {
    //         printf(" %s\n", "Black");
    //         put_piece(BLACK, new_pos, board_state, last_put);
    //     }
    //     else {
    //         printf(" %s\n", "White");
    //         put_piece(WHITE, new_pos, board_state, last_put);
    //     }
    //     free(new_pos_str);
    //     free(new_pos);
    //     draw_board(board_state, last_put);
    // }
    printf("man_man");
    system("pause");
}

// Man-machine combat
void man_machine() {
    // Initialize board state:
    // 0: No space whatsoever
    // 1: White piece
    // 2: Black piece
    int board_state[BOARD_SIZE][BOARD_SIZE] = {};

    // Initialize position last put (default -1, -1)
    // All positions are (line, column) from 0 up.
    // Example: A15 (0, 0) | O15 (0, 14) | 
    int last_put[2] = {-1, -1};                     
    printf("man_machine");
    system("pause");

}

// Machine-man combat
void machine_man() {
    // Initialize board state:
    // 0: No space whatsoever
    // 1: White piece
    // 2: Black piece
    int board_state[BOARD_SIZE][BOARD_SIZE] = {};

    // Initialize position last put (default -1, -1)
    // All positions are (line, column) from 0 up.
    // Example: A15 (0, 0) | O15 (0, 14) | 
    int last_put[2] = {-1, -1};                     
    printf("machine_man");
    system("pause");

}

// Machine-machine combat (only for training/testing purposes)
void machine_machine() {
    // Initialize board state:
    // 0: No space whatsoever
    // 1: White piece
    // 2: Black piece
    int board_state[BOARD_SIZE][BOARD_SIZE] = {};

    // Initialize position last put (default -1, -1)
    // All positions are (line, column) from 0 up.
    // Example: A15 (0, 0) | O15 (0, 14) | 
    int last_put[2] = {-1, -1};                     
    printf("machine_machine");
    system("pause");

}
