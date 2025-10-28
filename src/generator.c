#include <stdlib.h>
#include <time.h>
#include "generator.h"
#include "solver.h"
#include "sudoku.h"

// ---- Helper: swap two integers ----
static void swap_int(int *a, int *b) {
    int t = *a; *a = *b; *b = t;
}

// ---- Step 1: Fill diagonal 3x3 boxes ----
static void fill_diagonal_boxes(int grid[N][N]) {
    for (int k = 0; k < N; k += 3) {
        int nums[9] = {1,2,3,4,5,6,7,8,9};
        for (int i = 0; i < 9; i++) {
            int j = rand() % 9;
            swap_int(&nums[i], &nums[j]);
        }
        int idx = 0;
        for (int r = 0; r < 3; r++)
            for (int c = 0; c < 3; c++)
                grid[r + k][c + k] = nums[idx++];
    }
}

// ---- Step 2: Generate a full valid solved grid ----
void generate_full_grid(int grid[N][N]) {
    // clear grid
    for (int r = 0; r < N; r++)
        for (int c = 0; c < N; c++)
            grid[r][c] = UNASSIGNED;

    fill_diagonal_boxes(grid);
    solve_sudoku(grid);  // backtracking fills remaining cells
}

// ---- Step 3: Remove cells based on difficulty ----
void remove_cells(int grid[N][N], Difficulty level) {
    int blanks;
    switch (level) {
        case BEGINNER: blanks = rand() % 6 + 35; break;        // 35–40 blanks
        case INTERMEDIATE: blanks = rand() % 6 + 45; break;    // 45–50 blanks
        case EXPERT: blanks = rand() % 6 + 55; break;          // 55–60 blanks
        default: blanks = 40;
    }

    while (blanks > 0) {
        int row = rand() % 9;
        int col = rand() % 9;

        if (grid[row][col] != UNASSIGNED) {
            int backup = grid[row][col];
            grid[row][col] = UNASSIGNED;

            int copy[N][N];
            copy_grid(grid, copy);
            int count = count_solutions(copy, 2);

            if (count != 1) {  // not unique
                grid[row][col] = backup;
                continue;
            }
            blanks--;
        }
    }
}

// ---- Step 4: Combined function ----
void generate_puzzle(int grid[N][N], Difficulty level) {
    srand(time(NULL));
    generate_full_grid(grid);
    remove_cells(grid, level);
}
