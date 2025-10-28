#ifndef HINT_H
#define HINT_H

#include "sudoku.h"

void init_hints(int difficulty);
int get_hint_count(void);
void give_hint(int puzzle[N][N], int solution[N][N]);

#endif
