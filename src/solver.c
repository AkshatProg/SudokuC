#include "solver.h"

static bool solve_recursive(int grid[N][N]) {
    int row, col;
    if (!find_unassigned(grid, &row, &col)) return true; // solved

    for (int num = 1; num <= 9; num++) {
        if (is_safe(grid, row, col, num)) {
            grid[row][col] = num;
            if (solve_recursive(grid)) return true;
            grid[row][col] = UNASSIGNED; // backtrack
        }
    }
    return false;
}

bool solve_sudoku(int grid[N][N]) {
    return solve_recursive(grid);
}

// helper for generator uniqueness check
static int count_solutions_recursive(int grid[N][N], int limit) {
    int row, col;
    if (!find_unassigned(grid, &row, &col)) return 1;

    int count = 0;
    for (int num = 1; num <= 9 && count < limit; num++) {
        if (is_safe(grid, row, col, num)) {
            grid[row][col] = num;
            count += count_solutions_recursive(grid, limit - count);
            grid[row][col] = UNASSIGNED;
        }
    }
    return count;
}

int count_solutions(int grid[N][N], int limit) {
    return count_solutions_recursive(grid, limit);
}
