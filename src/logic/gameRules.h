#ifndef GAMERULES
#define GAMERULES

#include "../data/gameField.h"

#define bool char
#define TRUE 1
#define FALSE 0

void applyRules(GameField * gameField);

bool ifTrueCheckIfCellIsAlive(bool condition, char * cell);

#endif
