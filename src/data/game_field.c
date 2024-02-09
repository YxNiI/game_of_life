#include <stdlib.h>

#include "./game_field.h"

char ** create_game_field(int rows, int cols)
{
  game_field * game_field = (game_field *) malloc(sizeof(game_field));
  char
  
  char ** game_field = (char **) malloc(rows * sizeof(char *));
  for (int row = 0; row < rows; ++row)
    {
      game_field[row] = (char *) malloc(cols * sizeof(char));
    }

  return game_field;
}

int placeCells(char ** game_field, unsigned int seed)
{
}
