#ifndef SOLVER_H
#define SOLVER_H

#include <stdbool.h>
#include "sudoku.h"

bool solve_sudoku(int grid[N][N]);
int count_solutions(int grid[N][N], int limit);

#endif
