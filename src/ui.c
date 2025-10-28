#define RESET   "\x1b[0m"
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define CYAN    "\x1b[36m"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "ui.h"
#include "sudoku.h"
#include "solver.h"
#include "generator.h"
#include "hint.h"
#include "fileio.h"
#include <time.h>

static void clear_input(void)
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;
}

void show_intro(void)
{
    printf(CYAN "====================================\n");
    printf("         SUDOKU - C ENGINE\n");
    printf("====================================\n" RESET);

}

void show_menu(void)
{
    printf("\nSelect Difficulty:\n");
    printf("1. Beginner (35–40 blanks)\n");
    printf("2. Intermediate (45–50 blanks)\n");
    printf("3. Expert (55–60 blanks)\n");
    printf("0. Exit\n");
}

void play_game(void)
{
    int choice;
    while (1)
    {
        show_menu();
        printf("> ");
        if (scanf("%d", &choice) != 1)
        {
            clear_input();
            continue;
        }

        if (choice == 0)
        {
            printf("Goodbye!\n");
            return;
        }
        if (choice < 1 || choice > 3)
        {
            printf("Invalid choice.\n");
            continue;
        }

        Difficulty level = (Difficulty)choice;

        int puzzle[N][N];
        generate_puzzle(puzzle, level);

        int original[N][N];
        copy_grid(puzzle, original);

        int solution[N][N];
        copy_grid(puzzle, solution);
        solve_sudoku(solution); // Precompute solved version

        init_hints(choice); // Initialize hints for selected difficulty
        time_t start_time = time(NULL);

        printf("\nYour puzzle:\n");
        print_grid(puzzle);

        printf("\nYou can:\n");
        printf(" - Enter moves as 'row col val' (e.g. 1 3 4)\n");
        printf(" - Type 'hint' to use a hint (limited)\n");
        printf(" - Enter '0 0 0' to return to menu\n");

        int row, col, val;
        char input[20];

        while (1)
        {
            printf("\nEnter command: ");
            if (scanf("%s", input) != 1)
            {
                clear_input();
                continue;
            }

            // Player wants a hint
            if (strcmp(input, "hint") == 0)
            {
                give_hint(puzzle, solution);
                print_grid(puzzle);
                continue;
            }

            // Player entered 3 numbers
            row = atoi(input);
            if (scanf("%d %d", &col, &val) != 2)
            {
                clear_input();
                continue;
            }

            // Quit
            if (row == 0 && col == 0 && val == 0)
            {
                printf("Returning to menu...\n");
                break;
            }

            // Bounds check
            if (row < 1 || row > 9 || col < 1 || col > 9 || val < 1 || val > 9)
            {
                printf("❌ Values must be between 1–9.\n");
                continue;
            }

            row--;
            col--;

            // Prevent editing original clues
            if (original[row][col] != UNASSIGNED)
            {
                printf("⚠️  Can't change original clue.\n");
                continue;
            }

            // Check if valid move
            if (is_safe(puzzle, row, col, val))
            {
                puzzle[row][col] = val;
             printf(GREEN "✅ Placed %d at (R%d, C%d)\n" RESET, val, row + 1, col + 1);

            }
            else
            {
                printf(RED "❌ Invalid move (conflict).\n" RESET);

            }

            print_grid(puzzle);

            // Check if puzzle is complete
            bool complete = true;
            for (int r = 0; r < N; r++)
                for (int c = 0; c < N; c++)
                    if (puzzle[r][c] == UNASSIGNED)
                        complete = false;

            // if (complete) {
            //     int temp[N][N];
            //     copy_grid(puzzle, temp);
            //     if (solve_sudoku(temp)) {
            //         printf("\n🎉 Congratulations! You solved the puzzle!\n");
            //         printf("Hints used: %d\n", (choice == 1 ? 10 : choice == 2 ? 6 : 3) - get_hint_count());
            //         return;
            //     }
            // }
            if (complete)
            {
                int temp[N][N];
                copy_grid(puzzle, temp);
                if (solve_sudoku(temp))
                {
                    printf(GREEN "\n🎉 Congratulations! You solved the puzzle!\n" RESET);


                    time_t end_time = time(NULL);
                    int elapsed = (int)difftime(end_time, start_time);

                    int total_hints = (choice == 1 ? 10 : choice == 2 ? 6
                                                                      : 3);
                    int used = total_hints - get_hint_count();

                    printf("Hints used: %d\n", used);
                    printf("🕒 Time taken: %02d:%02d\n", elapsed / 60, elapsed % 60);

                    char player_name[50] = "Akshat"; // You can later make this user input
                    save_game_stats(player_name, level, used, elapsed);

                    printf("✅ Stats saved to assets/stats.txt\n");

                    return;
                }
            }
        }
    }
}
