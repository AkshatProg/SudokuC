#ifndef GENERATOR_H
#define GENERATOR_H

#include "sudoku.h"

typedef enum {
    BEGINNER = 1,
    INTERMEDIATE,
    EXPERT
} Difficulty;

void generate_full_grid(int grid[N][N]);
void remove_cells(int grid[N][N], Difficulty level);
void generate_puzzle(int grid[N][N], Difficulty level);

#endif
