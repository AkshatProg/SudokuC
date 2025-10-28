#include <stdio.h>
#include <stdlib.h>
#include "hint.h"
#include "solver.h"
#include "sudoku.h"
#include "colors.h"


static int hints_left = 0;

void init_hints(int difficulty) {
    switch (difficulty) {
        case 1: hints_left = 10; break; // Beginner
        case 2: hints_left = 6;  break; // Intermediate
        case 3: hints_left = 3;  break; // Expert
        default: hints_left = 5;
    }
}

int get_hint_count(void) {
    return hints_left;
}

void give_hint(int puzzle[N][N], int solution[N][N]) {
    if (hints_left <= 0) {
        printf("⚠️  No hints left!\n");
        return;
    }

    // Find first empty cell
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < N; c++) {
            if (puzzle[r][c] == UNASSIGNED) {
                puzzle[r][c] = solution[r][c];
                printf(YELLOW "💡 Hint: Cell (R%d, C%d) is %d\n" RESET, r + 1, c + 1, solution[r][c]);
                hints_left--;
                printf("Hints left: %d\n", hints_left);
                return;
            }
        }
    }

    printf("✅ Puzzle already complete — no hints needed!\n");
}
