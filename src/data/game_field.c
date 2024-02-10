#include <stdlib.h>

#include "./game_field.h"

t_game_field * create_game_field(int rows, int cols)
{
  t_game_field * game_field = (t_game_field *) malloc(sizeof(t_game_field));  

  game_field->rows = rows;
  game_field->cols = cols;

  game_field->field = (char **) malloc(rows * (sizeof(char *)));
  char ** field = game_field->field;
  for (int row = 0; row < rows; ++row)
    {
      field[row] = (char *) malloc(cols * sizeof(char));

      for (int col = 0; col < cols; ++col)
	{
	  field[row][col] = DEAD_CELL;
	}      
    }

  return game_field;
}

int set_alive_cells_random(t_game_field * game_field, unsigned int seed)
{
  unsigned int rows = game_field->rows;
  unsigned int cols = game_field->cols;
  
  unsigned int row_cell_placement_start = rows / 4;
  unsigned int row_cell_placement_end = row_cell_placement_start + (rows / 2);
  unsigned int col_cell_placement_start = cols / 4;
  unsigned int col_cell_placement_end = col_cell_placement_start + (cols / 2);
  
  srand(seed);
  unsigned int alive_cells = 0;

  for (unsigned int row = row_cell_placement_start; row < row_cell_placement_end; ++row)
    {
      for (unsigned int col = col_cell_placement_start; col < col_cell_placement_end; ++col)
	{
	  unsigned int randomTrueOrFalse = rand() % (1 + 1);
	  
	  if (randomTrueOrFalse)
	    {
	      game_field->field[row][col] = ALIVE_CELL;
	      ++alive_cells;
	    }
	}
    }
  
  return alive_cells;
}
