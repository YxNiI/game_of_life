#ifndef GAMEFIELD
#define GAMEFIELD

#define ALIVE_CELL 'X'
#define DEAD_CELL ' '

typedef struct
{
  int rows;
  int cols;
  char ** field;
} GameField;

GameField * createGameField(int rows, int cols);

void destroy(GameField * gameField);

void setRandomCellsAlive(GameField * gameField);

#endif
