#include "ai_move.h"

unsigned long long zobrist_hash = 0;
HashTable* ht = NULL;
Move moves[BOARD_SIZE * BOARD_SIZE] = {0};
int moves_count = 0;

int req_count = 0;
int hashed_count = 0;


/**
 * @brief Initialize zobrist hash and hashtable.
*/
void initialize() {
    ht = create_hashtable();
    initializeZobrist();
    zobrist_hash = computeZobristHash((int [15][15]){
    //  0  1  2  3  4  5  6  7  8  9 10 11 12 13 14
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 0
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 1
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 2
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 3
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 4
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 5
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 6
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 7
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 8
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 9
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 10
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 11
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 12
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 13
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // 14
    });
}

void push_move(Position pos, Pair scores, int player) {
    moves[moves_count].pos = pos;
    moves[moves_count].scores = scores;
    moves[moves_count].player = player;
    ++moves_count;
}

Move pop_move() {
    return moves[--moves_count];
}

/**
 * @brief AI makes a move
 *
 * @param[in] board_state    current board state
 * @param[in] player         player to move
 * @param[in] role_computer  role of the computer
 * @retval Position          position to put the piece
 */
Position move(int board_state[][BOARD_SIZE], int player, int role_computer) {
    Move_t best_move = alpha_beta(board_state, TOTAL_DEPTH, NEG_INFINITY, INFINITY, player, role_computer);
    return best_move.pos;
}

/**
 * @brief Put a piece on the board in AI mode.
 *
 * @param color The color of the piece to put (BLACK or WHITE).
 * @param pos The position to put the piece.
 * @param board_state The current state of the board.
 * @param role_computer The role of the computer (AI).
 */
void AI_put_piece(int color, Position pos, int board_state[][BOARD_SIZE], int role_computer) {
    unsigned long long original_hash = zobrist_hash;
    zobrist_hash = updateZobristHash(zobrist_hash, NONE, color, pos);

    Pair scores = (Pair){0, 0};

    int s = search_node(ht, zobrist_hash, &scores);

    req_count += 1;

    if (s == -1) { // No score of such board state is stored. scores remains (0, 0)
        int old_score_black = evaluate_star(board_state, pos, BLACK);
        int old_score_white = evaluate_star(board_state, pos, WHITE);

        board_state[pos.x][pos.y] = color;

        int new_score_black = evaluate_star(board_state, pos, BLACK);
        int new_score_white = evaluate_star(board_state, pos, WHITE);

        search_node(ht, original_hash, &scores);
        scores.score_black += new_score_black - old_score_black;
        scores.score_white += new_score_white - old_score_white;

        insert_node(ht, zobrist_hash, scores);
    }
    else {
        hashed_count += 1;
        board_state[pos.x][pos.y] = color;
    }

    push_move(pos, scores, color);
}

void AI_remove_piece(int board_state[][BOARD_SIZE], int role_computer) {
    Move last_move = pop_move();
    Position pos = last_move.pos;
    unsigned long long original_hash = zobrist_hash;
    zobrist_hash = updateZobristHash(zobrist_hash, board_state[pos.x][pos.y], NONE, pos);

    Pair scores = (Pair){0, 0};

    int s = search_node(ht, zobrist_hash, &scores);
    if (s == -1) {
        // No scores of such board state is stored.
        // This should not happen, but added for fail-safe.
        int old_score_black = evaluate_star(board_state, pos, BLACK);
        int old_score_white = evaluate_star(board_state, pos, WHITE);

        board_state[pos.x][pos.y] = NONE;

        int new_score_black = evaluate_star(board_state, pos, BLACK);
        int new_score_white = evaluate_star(board_state, pos, WHITE);

        search_node(ht, original_hash, &scores);
        scores.score_black += new_score_black - old_score_black;
        scores.score_white += new_score_white - old_score_white;

        insert_node(ht, zobrist_hash, scores);
    }
    else {
        board_state[pos.x][pos.y] = NONE;
    }
}


/**
 * @brief Performs the alpha-beta pruning algorithm to determine the best move in a Renju game.
 *
 * @param board_state The current state of the game board.
 * @param depth The remaining depth of the search tree.
 * @param alpha The alpha value for alpha-beta pruning.
 * @param beta The beta value for alpha-beta pruning.
 * @param player The player to put the next piece.
 * @param role_computer The role of the computer player.
 * @return The best move determined by the alpha-beta pruning algorithm.
 */
Move_t alpha_beta(int board_state[][BOARD_SIZE], int depth, int alpha, int beta, int player, int role_computer) {
    Move_t move_to_return = (Move_t){.pos = (Position){-1, -1}, .score_used = 0};
    int next_player = (player == BLACK) ? WHITE : BLACK;

    Position available_moves[BOARD_SIZE * BOARD_SIZE] = {(Position){0, 0}};
    int count = find_available_moves(board_state, player, available_moves);

    if (depth == 0 || count == 0) {
        if (role_computer == BLACK) { // maximizing player
            if (player == BLACK) {
                move_to_return.score_used = - moves[moves_count - 1].scores.score_white;
            }
            move_to_return.score_used = moves[moves_count - 1].scores.score_black;
        }
        else { // role_computer == WHITE
            if (player == BLACK) {
                move_to_return.score_used = moves[moves_count - 1].scores.score_white;
            }
            move_to_return.score_used = - moves[moves_count - 1].scores.score_black;
        }
        return move_to_return;
    }

    if (player == role_computer) {  // our side (maximizing player)
        move_to_return.score_used = NEG_INFINITY;

        for (int i = 0; i < count; ++i) {
            Position pos = available_moves[i];
            AI_put_piece(player, pos, board_state, role_computer);
            Move_t attempted_move = alpha_beta(board_state, depth - 1, alpha, beta, next_player, role_computer);
            AI_remove_piece(board_state, role_computer);

            if (attempted_move.score_used > move_to_return.score_used) {
                move_to_return.score_used = attempted_move.score_used;
                move_to_return.pos = pos;
            }
            alpha = max(alpha, move_to_return.score_used);

            if (beta <= alpha) {
                break;
            }
        }
    }
    else {  // other side (minimizing player)
        move_to_return.score_used = INFINITY;

        for (int i = 0; i < count; ++i) {
            Position pos = available_moves[i];
            AI_put_piece(player, pos, board_state, role_computer);
            Move_t attempted_move = alpha_beta(board_state, depth - 1, alpha, beta, next_player, role_computer);
            // printf("Attempted move: at  pos (%d, %d), score: %d\n", attempted_move.pos.x, attempted_move.pos.y, attempted_move.score_used);
            AI_remove_piece(board_state, role_computer);

            if (attempted_move.score_used < move_to_return.score_used) {
                move_to_return.score_used = attempted_move.score_used;
                move_to_return.pos = pos;
            }
            beta = min(beta, move_to_return.score_used);

            if (beta <= alpha) {
                break;
            }
        }
    }
    return move_to_return;
}

int find_available_moves(int board_state[][BOARD_SIZE], int player, Position* available_moves) {
    int count = 0;

    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (board_state[i][j]) {
                // Put blank positions in (i - 2, i + 2) * (j - 2, j + 2) into available_moves
                for (int x = i - 1; x <= i + 1; ++x) {
                    for (int y = j - 1; y <= j + 1; ++y) {
                        if (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE && board_state[x][y] == NONE) {
                            if (player == BLACK && check_forbidden_move(board_state, (int[]){x, y}, WHITE)) {}
                            else {
                                // If (x, y) not in available_moves, then add it
                                int flag = 0;
                                for (int k = 0; k < count; ++k) {
                                    if (available_moves[k].x == x && available_moves[k].y == y) {
                                        flag = 1;
                                        break;
                                    }
                                }
                                if (!flag) {
                                    available_moves[count++] = (Position){x, y};
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return count;
}

void print_counts() {
    printf("Total score requests: %d, hashed: %d, rate %f.\n", req_count, hashed_count, (double)hashed_count/req_count);
}
