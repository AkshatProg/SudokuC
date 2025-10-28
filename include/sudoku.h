#ifndef SUDOKU_H
#define SUDOKU_H

#include <stdbool.h>

#define N 9
#define UNASSIGNED 0

bool is_safe(int grid[N][N], int row, int col, int num);
bool find_unassigned(int grid[N][N], int *row, int *col);
void print_grid(int grid[N][N]);
void copy_grid(int src[N][N], int dest[N][N]);

#endif
