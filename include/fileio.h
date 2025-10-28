#ifndef FILEIO_H
#define FILEIO_H

#include "generator.h"

void save_game_stats(const char *player, Difficulty level, int hints_used, int seconds);
const char *difficulty_name(Difficulty d);

#endif
