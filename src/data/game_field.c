#include <stdlib.h>

#include "./game_field.h"

char ** create_game_field(int rows, int cols)
{
  char ** game_field = (char **) malloc(rows * sizeof(char *));
  for (int row = 0; row < rows; ++row)
    {
      game_field[row] = (char *) malloc(cols * sizeof(char));
    }

  for (int row = 0; row < rows; ++row)
    {
      for (int col = 0; col < cols; ++col)
	{
	  game_field[row][col] = DEAD_CELL;	
	}
    }

  return game_field;
}
