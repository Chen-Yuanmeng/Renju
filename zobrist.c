#include "zobrist.h"

unsigned long long zobrist[BOARD_SIZE][BOARD_SIZE][3];

void initializeZobrist() {
    Xorshift64 rng;
    rng.a = 123456789;

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            for (int k = 0; k < 3; k++) {
                zobrist[i][j][k] = xorshift64_rand(&rng);
            }
        }
    }
}

unsigned long long computeZobristHash(int board[BOARD_SIZE][BOARD_SIZE]) {
    unsigned long long hash = 0;

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            int state = board[i][j];  // Current state of the board
            hash ^= zobrist[i][j][state];  // Update the hash value
        }
    }

    return hash;
}

// Update the Zobrist hash value
unsigned long long updateZobristHash(unsigned long long currentHash, int oldState, int newState, Position pos) {
    currentHash ^= zobrist[pos.x][pos.y][oldState];  // Remove the old state's hash value
    currentHash ^= zobrist[pos.x][pos.y][newState];  // Add the new state's hash value
    return currentHash;
}
