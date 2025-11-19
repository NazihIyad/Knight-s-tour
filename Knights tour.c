#include <stdio.h>
#include <stdbool.h>
#define SIZE 8        
#define MOVE_COUNT 8

const int MOVES_X[MOVE_COUNT] = {2, 1, -1, -2, -2, -1, 1, 2};
const int MOVES_Y[MOVE_COUNT] = {1, 2, 2, 1, -1, -2, -2, -1};

typedef int board_t[SIZE][SIZE];

bool move_is_possible(size_t move_id, size_t x, size_t y, board_t visited) {
    int new_x = x + MOVES_X[move_id];
    int new_y = y + MOVES_Y[move_id];

    if (new_x < 0 || new_x >= SIZE || new_y < 0 || new_y >= SIZE)
        return false;

    if (visited[new_y][new_x] != 0)
        return false;

    return true;
}

unsigned int tour_greedy(size_t start_x, size_t start_y) {
    board_t visited = {0};
    size_t x = start_x;
    size_t y = start_y;
    unsigned int move_count = 1;

    visited[y][x] = move_count; 

    bool move_found = true;
    while (move_found) {
        move_found = false;
        for (size_t move_id = 0; move_id < MOVE_COUNT; move_id++) {
            if (move_is_possible(move_id, x, y, visited)) {
                x += MOVES_X[move_id];
                y += MOVES_Y[move_id];
                visited[y][x] = ++move_count;
                move_found = true;
                break; 
            }
        }
    }

    printf("Start at (%zu, %zu) — visited %u squares:\n", start_x, start_y, move_count);
    for (size_t i = 0; i < SIZE; i++) {
        for (size_t j = 0; j < SIZE; j++) {
            printf("%3d ", visited[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    return move_count;
}

void greedy_tour_from_each_square() {
    for (size_t y = 0; y < SIZE; y++) {
        for (size_t x = 0; x < SIZE; x++) {
            tour_greedy(x, y);
        }
    }
}

int main() {
    greedy_tour_from_each_square();
    return 0;
}
