#include "board_io.h"

// Convert {0, 0} to "A15", {14, 14} to "O1", etc
// Beware: free memory afterwards using `free(result);`
char* position_to_string(int pos[]) {
    char* pos_str = (char*) malloc(4 * sizeof(char));

    pos_str[0] = (char)('A' + pos[1]);

    if (pos[0] < 6) {    //  comes from (15 - pos[0] > 9)
        pos_str[1] = '1';
        pos_str[2] = '0' + 5 - pos[0];
        pos_str[3] = '\0';
    }
    else {
        pos_str[1] = '0' + 15 - pos[0];
        pos_str[2] = '\0';
    }

    return pos_str;
}

// Convert "A15" to {0, 0}, "O1" to {14, 14}, etc
// Beware: free memory afterwards using `free(result);`
int* string_to_position(char pos[]) {
    int* pos_int = (int*) malloc(2* sizeof(int));

    if (pos[2] == '\0') {
        pos_int[0] = '0' + 15 - pos[1];
    }
    else {
        pos_int[0] = '0' + 5 - pos[2];
    }

    pos_int[1] = pos[0] - 'A';

    return pos_int;
}

// Get input position as string, example "A15"
// Beware: free memory afterwards using `free(result);`
char* get_input_position(char prompt[]) {
    char* new_pos = (char*) malloc(4 * sizeof(char));

    printf("%s", prompt);
    scanf_s("%3s", new_pos, 4);

    return new_pos;
}

// Prompts user to put next piece.
// `int next`: BLACK or WHITE
void put_piece_prompt(int next, int board_state[][BOARD_SIZE], int last_put[]) {
    char next_piece_string[4];
    assert(next == BLACK || next == WHITE);

    if (next == BLACK) {
        printf("BLACK to go.\nPlease tell me where to place the next black piece: ");
    }
    else {
        printf("WHITE to go.\nPlease tell me where to place the next white piece: ");
    }

    char* to_put_str;
    int* new_pos;
    to_put_str = get_input_position("");
    new_pos = string_to_position(to_put_str);

    put_piece(next, new_pos, board_state, last_put);

    free(to_put_str);
    free(new_pos);
}
