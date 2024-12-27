// This file defines multiple modes in Renju program:

#include "mode.h"

// Man-man combat
void man_man() {
    // Initialize board state:
    // 0: No piece whatsoever
    // 1: White piece `WHITE`
    // 2: Black piece `BLACK`
    int board_state[BOARD_SIZE][BOARD_SIZE] = {0};

    // Initialize position last put (default -1, -1)
    // All positions are (line, column) from 0 up.
    // Example: A15 (0, 0) | O15 (0, 14) | 
    int last_put[2] = {-1, -1};
    
    // Put first piece at H8
    int first_position[2] = {7, 7};
    put_piece(BLACK, first_position, board_state, last_put);
    draw_board(board_state, last_put);
    printf("The first Black piece has been put at H8 for you.\nPress any key to continue...\n");
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

// Man-machine combat: man goes first (black) 
void man_machine() { 
    int board_state[BOARD_SIZE][BOARD_SIZE] = {0};
    int last_put[2] = {-1, -1};

    initialize();

    // Man puts first piece at H8
    AI_put_piece(BLACK, (Position){7, 7}, board_state, WHITE);
    last_put[0] = 7;
    last_put[1] = 7;
    draw_board(board_state, last_put);
    printf("The first Black piece has been put at H8 for you.\nPress any key to continue...\n");
    system("pause > nul");
    // system("cls");
    draw_board(board_state, last_put);

    // Loop until status becomes true
    int status = 0;
    int next = WHITE;
    while (!status) {
        if (next == WHITE) {  // AI's turn
            printf("AI calculating...");
            clock_t start = clock();

            Position pos = move(board_state, WHITE, WHITE);
            AI_put_piece(WHITE, pos, board_state, WHITE);
            
            clock_t end = clock();
            last_put[0] = pos.x;
            last_put[1] = pos.y;
            next = BLACK;
            // system("cls");
            draw_board(board_state, last_put);
            printf("Time: %fs\n", (double)(end - start) / CLOCKS_PER_SEC);
            printf("AI has put a piece at %s.\nPress any key to continue...\n", position_to_string((int[]){pos.x, pos.y}));
            status = check(board_state, last_put, next);
            check_prompt(status);
        }
        else {  // human's turn
            int pos[2] = {-1, -1};
            put_piece_prompt(next, board_state, pos);
            AI_put_piece(next, (Position){pos[0], pos[1]}, board_state, WHITE);
            last_put[0] = pos[0];
            last_put[1] = pos[1];
            next = WHITE;
            // system("cls");
            draw_board(board_state, last_put);
            status = check(board_state, last_put, next);
            check_prompt(status);
        }
        print_counts();
    };
}

// Machine-man combat
void machine_man() {
    int board_state[BOARD_SIZE][BOARD_SIZE] = {0};
    int last_put[2] = {-1, -1};

    initialize();

    // Man puts first piece at H8
    AI_put_piece(BLACK, (Position){7, 7}, board_state, BLACK);
    last_put[0] = 7;
    last_put[1] = 7;
    draw_board(board_state, last_put);
    printf("The first Black piece has been put at H8 for you.\nPress any key to continue...\n");
    system("pause > nul");
    // system("cls");
    draw_board(board_state, last_put);

    // Loop until status becomes true
    int status = 0;
    int next = WHITE;
    while (!status) {
        if (next == BLACK) {  // AI's turn
            printf("AI calculating...");
            clock_t start = clock();

            Position pos = move(board_state, BLACK, BLACK);
            AI_put_piece(BLACK, pos, board_state, BLACK);
            
            clock_t end = clock();
            last_put[0] = pos.x;
            last_put[1] = pos.y;
            next = WHITE;
            // system("cls");
            draw_board(board_state, last_put);
            printf("Time: %fs\n", (double)(end - start) / CLOCKS_PER_SEC);
            printf("AI has put a piece at %s.\nPress any key to continue...\n", position_to_string((int[]){pos.x, pos.y}));
            status = check(board_state, last_put, next);
            check_prompt(status);
        }
        else {  // human's turn
            int pos[2] = {-1, -1};
            put_piece_prompt(next, board_state, pos);
            AI_put_piece(next, (Position){pos[0], pos[1]}, board_state, BLACK);
            last_put[0] = pos[0];
            last_put[1] = pos[1];
            next = BLACK;
            // system("cls");
            draw_board(board_state, last_put);
            status = check(board_state, last_put, next);
            check_prompt(status);
        }
        print_counts();
    };
}

// Machine-machine combat (only for training/testing purposes)
void machine_machine() {
    int board_state[BOARD_SIZE][BOARD_SIZE] = {0};
    int last_put[2] = {-1, -1};

    initialize();

    // Man puts first piece at H8
    AI_put_piece(BLACK, (Position){7, 7}, board_state, BLACK);
    last_put[0] = 7;
    last_put[1] = 7;
    draw_board(board_state, last_put);
    printf("The first Black piece has been put at H8 automatically.\n");
    // system("cls");
    draw_board(board_state, last_put);

    // Loop until status becomes true
    int status = 0;
    int next = WHITE;
    while (!status) {
        if (next == BLACK) {  // AI black's turn
            clock_t start = clock();

            Position pos = move(board_state, BLACK, BLACK);
            AI_put_piece(BLACK, pos, board_state, BLACK);
            
            clock_t end = clock();
            last_put[0] = pos.x;
            last_put[1] = pos.y;
            next = WHITE;
            // system("cls");
            draw_board(board_state, last_put);
            printf("Time: %fs\n", (double)(end - start) / CLOCKS_PER_SEC);
            printf("AI black has put a piece at %s.\nPress any key to continue...\n", position_to_string((int[]){pos.x, pos.y}));
            status = check(board_state, last_put, next);
            check_prompt(status);
        }
        else {  // AI white's turn
            clock_t start = clock();

            Position pos = move(board_state, WHITE, WHITE);
            AI_put_piece(WHITE, pos, board_state, WHITE);
            
            clock_t end = clock();
            last_put[0] = pos.x;
            last_put[1] = pos.y;
            next = BLACK;
            // system("cls");
            draw_board(board_state, last_put);
            printf("Time: %fs\n", (double)(end - start) / CLOCKS_PER_SEC);
            printf("AI white has put a piece at %s.\nPress any key to continue...\n", position_to_string((int[]){pos.x, pos.y}));
            status = check(board_state, last_put, next);
            check_prompt(status);
        }
        print_counts();
        printf("Waiting 2 seconds before next move...\n");
        sleep(2);
        printf("AI calculating...");
    };

}
