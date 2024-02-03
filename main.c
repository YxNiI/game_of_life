#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BOOL char
#define FALSE 0
#define TRUE 1

#define ALIVE_CELL 'X'
#define DEAD_CELL '_'

/*
 * 1. Jede Zelle mit weniger als zwei lebenden Nachbarn stirbt.
 * 2. Jede Zelle mit zwei oder drei Nachbarn lebt weiter, zur nächsten Generation.
 - Jede Iteration ist eine Generation.
 * 3. Jede Zelle mit mehr als drei Nachbarn stirbt.
 * 4. Jede Zelle mit exakt drei Nachbarn erwacht zum Leben.
 */

int getRandomZeroOrOne();

int main()
{
  int rows = 25;
  int cols = 50;
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

  int alive_cells = (rows + cols) / 2;

  srand(4242);

  int row_cell_placement_start = rows / 4;
  int row_cell_placement_end = row_cell_placement_start + (rows / 2);
  int col_cell_placement_start = cols / 4;
  int col_cell_placement_end = col_cell_placement_start + (cols / 2);

  for (int row = row_cell_placement_start; row < row_cell_placement_end; ++row)
    {
      for (int col = col_cell_placement_start; col < col_cell_placement_end; ++col)
	{
	  unsigned int trueOrFalse = rand() % (1 + 1);
	  
	  if (trueOrFalse)
	    {
	      game_field[row][col] = ALIVE_CELL;
	    }
	  else
	    {
	      game_field[row][col] = DEAD_CELL;
	    }
	}
    }

  while (alive_cells > 0)
    {
      for (int row = 0; row < rows; ++row)
	{	 
	  for (int col = 0; col < cols; ++col)
	    {
	      printf("%c", game_field[row][col]);
	    }

	  printf("\n");
	}

      printf("-------------------------------------------------------");
      sleep(1);
      
      for (int row = 0; row < rows; ++row)
	{
	  for (int col = 0; col < cols; ++col)
	    {
	      int alive_neighbour_cells = 0;

	      int row_up = row - 1;
	      int row_down = row + 1;
	      int col_right = col + 1;
	      int col_left = col - 1;

	      if (row_up >= 0)
		{
		  alive_neighbour_cells += (game_field[row_up][col] == ALIVE_CELL) ? 1 : 0;
		}
	      if (row_down < rows)
		{
		  alive_neighbour_cells += (game_field[row_down][col] == ALIVE_CELL) ? 1 : 0;
		}
	      if (col_right < cols)
		{
		  alive_neighbour_cells += (game_field[row][col_right] == ALIVE_CELL) ? 1 : 0;
		}
	      if (col_left >= 0)
		{
		  alive_neighbour_cells += (game_field[row][col_left] == ALIVE_CELL) ? 1 : 0;
		}

	      if (alive_neighbour_cells < 2)
		{
		  game_field[row][col] = DEAD_CELL;
		  --alive_cells;
		}
	      else if (alive_neighbour_cells > 2 && alive_neighbour_cells < 3)
		{
		  game_field[row][col] = ALIVE_CELL;
		  ++alive_cells;
		}
	      else if (alive_neighbour_cells > 3)
		{
		  game_field[row][col] = DEAD_CELL;
		  --alive_cells;
		}
	      else if (alive_neighbour_cells == 3)
		{
		  game_field[row][col] = ALIVE_CELL;
		  ++alive_cells;
		}
	    }
	}
    }

  for (int row = 0; row < rows; ++row)
    {
      free(game_field[row]);
    }
  free(game_field);
  
  return 0; 
}
  
int getRandomZeroOrOne()
{
  return rand() % (1 + 1);
}
 
