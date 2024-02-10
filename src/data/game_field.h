#ifndef GAME_FIELD
#define GAME_FIELD

#define ALIVE_CELL 'X'
#define DEAD_CELL ' '

typedef struct
{
  int rows;
  int cols;
  char ** field;
} t_game_field;

t_game_field * create_game_field(int rows, int cols);

int placeCells(char ** game_field, unsigned int seed);

#endif
