#include "evaluate.h"

int evaluate_line(char line[], int perspective) {
    if (strlen(line) < 5) {
        return 0;
    }

    int score = 0;

    if (perspective == BLACK) {
        for (int i = 0; i < TOTAL_PATTERN; ++i) {
            score -= pattern_list[i].score_opponent * my_strstr(line, pattern_list[i].pattern_white);
            score += pattern_list[i].score_my * my_strstr(line, pattern_list[i].pattern_black);
        }
    }
    else {
        for (int i = 0; i < TOTAL_PATTERN; ++i) {
            score -= pattern_list[i].score_opponent * my_strstr(line, pattern_list[i].pattern_black);
            score += pattern_list[i].score_my * my_strstr(line, pattern_list[i].pattern_white);
        }
    }

    return score;
}

// Return the sum of the scores of the four directions at `pos` from the perspective of `role_computer`
int evaluate_star(int board_state[][BOARD_SIZE], Position pos, int role_computer) {
    char line[BOARD_SIZE + 1];
    char column[BOARD_SIZE + 1];
    char diag_1[BOARD_SIZE + 1];
    char diag_2[BOARD_SIZE + 1];

    get_line(board_state, pos.x, line);
    get_column(board_state, pos.y, column);
    get_diagonal_1(board_state, pos, diag_1);
    get_diagonal_2(board_state, pos, diag_2);

    return evaluate_line(line, role_computer) + evaluate_line(column, role_computer) + evaluate_line(diag_1, role_computer) + evaluate_line(diag_2, role_computer);
}

void get_line(int board_state[][BOARD_SIZE], int line_num, char line[]) {
    for (int j = 0; j < BOARD_SIZE; ++j) {
        line[j] = board_state[line_num][j] + '0';
    }
    line[BOARD_SIZE] = '\0';
}

void get_column(int board_state[][BOARD_SIZE], int column_num, char column[]) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        column[i] = board_state[i][column_num] + '0';
    }
    column[BOARD_SIZE] = '\0';
}

void get_diagonal_1(int board_state[][BOARD_SIZE], Position pos, char diag_1[]) {
    int i = pos.x - pos.y;
    int j = (i < 0) ? 0 : i;
    i = (i < 0) ? -i : 0;

    for (; i < BOARD_SIZE && j < BOARD_SIZE; ++i, ++j) {
        diag_1[i] = board_state[i][j] + '0';
    }
    diag_1[BOARD_SIZE] = '\0';
}

void get_diagonal_2(int board_state[][BOARD_SIZE], Position pos, char diag_2[]) {
    int i = pos.x + pos.y;
    int j = (i < BOARD_SIZE) ? 0 : i - BOARD_SIZE + 1;
    i = (i < BOARD_SIZE) ? i : BOARD_SIZE - 1;

    for (; i >= 0 && j < BOARD_SIZE; --i, ++j) {
        diag_2[BOARD_SIZE - 1 - i] = board_state[i][j] + '0';
    }
    diag_2[BOARD_SIZE] = '\0';
}
