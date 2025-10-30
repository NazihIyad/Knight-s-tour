#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

#define SIZE 8        
#define MOVE_COUNT 8  
const int MOVES_X[MOVE_COUNT] = { 2, 1, -1, -2, -2, -1, 1, 2 };
const int MOVES_Y[MOVE_COUNT] = { 1, 2,  2,  1, -1, -2, -2, -1 };
typedef unsigned int board_t[SIZE][SIZE];

bool move_is_possible(size_t move_id, int x, int y, board_t visited);

unsigned int tour_greedy(size_t start_x, size_t start_y);

void greedy_tour_from_each_square(void);

bool move_is_possible(size_t move_id, int x, int y, board_t visited)
{
    int new_x = x + MOVES_X[move_id];
    int new_y = y + MOVES_Y[move_id];

    if (new_x < 0 || new_y < 0 || new_x >= SIZE || new_y >= SIZE)
        return false;

    if (visited[new_y][new_x] != 0)
        return false;

    return true;
}

unsigned int tour_greedy(size_t start_x, size_t start_y)
{
    board_t visited = {0};  
    int x = start_x;
    int y = start_y;
    unsigned int steps = 1;

    visited[y][x] = steps;

    bool moved;
    do {
        moved = false;
        for (size_t move = 0; move < MOVE_COUNT; move++) {
            if (move_is_possible(move, x, y, visited)) {
                x += MOVES_X[move];
                y += MOVES_Y[move];
                steps++;
                visited[y][x] = steps;
                moved = true;
                break;  
            }
        }
    } while (moved);

    return steps;
}

void greedy_tour_from_each_square(void)
{
    board_t results = {0};

    for (size_t y = 0; y < SIZE; y++) {
        for (size_t x = 0; x < SIZE; x++) {
            results[y][x] = tour_greedy(x, y);
        }
    }

    printf("Greedy:\n");
    for (size_t y = 0; y < SIZE; y++) {
        for (size_t x = 0; x < SIZE; x++) {
            printf("%3u ", results[y][x]);
        }
        printf("\n");
    }
}

int main(void)
{
    greedy_tour_from_each_square();
    return 0;
}
