#include <stdio.h>
#include "sudoku.h"

bool used_in_row(int grid[N][N], int row, int num) {
    for (int c = 0; c < N; c++)
        if (grid[row][c] == num) return true;
    return false;
}

bool used_in_col(int grid[N][N], int col, int num) {
    for (int r = 0; r < N; r++)
        if (grid[r][col] == num) return true;
    return false;
}

bool used_in_box(int grid[N][N], int startRow, int startCol, int num) {
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            if (grid[startRow + r][startCol + c] == num) return true;
    return false;
}

bool is_safe(int grid[N][N], int row, int col, int num) {
    if (grid[row][col] != UNASSIGNED) return false;
    return !used_in_row(grid, row, num)
        && !used_in_col(grid, col, num)
        && !used_in_box(grid, row - row % 3, col - col % 3, num);
}

bool find_unassigned(int grid[N][N], int *row, int *col) {
    for (int r = 0; r < N; r++)
        for (int c = 0; c < N; c++)
            if (grid[r][c] == UNASSIGNED) {
                *row = r;
                *col = c;
                return true;
            }
    return false;
}

// void print_grid(int grid[N][N]) {
//     for (int r = 0; r < N; r++) {
//         if (r % 3 == 0) puts("+-------+-------+-------+");
//         for (int c = 0; c < N; c++) {
//             if (c % 3 == 0) putchar('|');
//             int v = grid[r][c];
//             printf(v ? " %d " : " . ", v);
//         }
//         puts("|");
//     }
//     puts("+-------+-------+-------+");
// }

// void print_grid(int grid[N][N]) {
//     printf("\n       ");
//     for (int c = 0; c < N; c++) {
//         printf("C%d ", c + 1);
//         if ((c + 1) % 3 == 0 && c != N - 1)
//             printf("  ");
//     }
//     printf("\n");

//     for (int r = 0; r < N; r++) {
//         if (r % 3 == 0)
//             printf("     +--------+---------+---------+\n");

//         printf("R%-2d |", r + 1);
//         for (int c = 0; c < N; c++) {
//             int v = grid[r][c];
//             if (v == UNASSIGNED) printf(" . ");
//             else printf(" %d ", v);
//             if ((c + 1) % 3 == 0) printf("|");
//         }
//         printf("\n");
//     }
//     printf("     +-------+-------+-------+\n");
// }
/* put this in src/sudoku.c, replacing the existing print_grid() */
void print_grid(int grid[N][N]) {
    /* column headers: each header takes 3 chars (e.g. "C1 "), add 2-space gap between 3x3 groups */
    printf("\n      ");                        // indent to align with "Rxx |"
    for (int c = 0; c < N; ++c) {
        printf("C%-2d", c + 1);               // prints like "C1 " (3 chars)
        if ((c + 1) % 3 == 0 && c != N - 1)  // gap between 3x3 blocks
            printf("  ");
    }
    printf("\n");

    /* top border */
    printf("    +-------+-------+-------+\n");

    for (int r = 0; r < N; ++r) {
        /* row label - fixed width so single/double digit rows align */
        printf("R%2d |", r + 1);              // "R 1 |" -> makes room for R10 if ever needed

        for (int c = 0; c < N; ++c) {
            int v = grid[r][c];
            if (v == UNASSIGNED) printf(" . ");
            else                printf(" %d ", v);

            /* vertical box divider every 3 cells */
            if ((c + 1) % 3 == 0) printf("|");
        }

        printf("\n");

        /* horizontal box divider after every 3 rows */
        if ((r + 1) % 3 == 0)
            printf("    +-------+-------+-------+\n");
    }
}


void copy_grid(int src[N][N], int dest[N][N]) {
    for (int r = 0; r < N; r++)
        for (int c = 0; c < N; c++)
            dest[r][c] = src[r][c];
}
