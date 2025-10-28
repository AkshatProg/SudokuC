#include <stdio.h>
#include <time.h>
#include "fileio.h"

const char *difficulty_name(Difficulty d) {
    switch (d) {
        case BEGINNER: return "Beginner";
        case INTERMEDIATE: return "Intermediate";
        case EXPERT: return "Expert";
        default: return "Unknown";
    }
}

void save_game_stats(const char *player, Difficulty level, int hints_used, int seconds) {
    FILE *fp = fopen("assets/stats.txt", "a");
    if (!fp) {
        perror("Error opening stats.txt");
        return;
    }

    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    fprintf(fp,
        "Player: %s | Difficulty: %s | HintsUsed: %d | Time: %02d:%02d | Date: %02d-%02d-%d\n",
        player,
        difficulty_name(level),
        hints_used,
        seconds / 60, seconds % 60,
        t->tm_mday, t->tm_mon + 1, 1900 + t->tm_year
    );

    fclose(fp);
}
