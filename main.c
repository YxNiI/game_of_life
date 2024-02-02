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

int getRandomNumber(int bound);

int main()
{
  int rows = 100;
  int cols = 100;
  char ** game_field = (char **) malloc(rows * sizeof(char *));

  for (int row = 0; row < cols; ++row)
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

  int alive_cells = 99;

  srand(4242);

  for (int row = 0; row < alive_cells; ++row)
    {
      game_field[getRandomNumber(alive_cells)][getRandomNumber(alive_cells)] = ALIVE_CELL;
    }

  while (alive_cells > 0)
    {
      
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

      for (int row = 0; row < rows; ++row)
	{	 
	  for (int col = 0; col < cols; ++col)
	    {
	      printf("%c", game_field[row][col]);
	    }

	  printf("\n");
	}

      sleep(1);
    }

  for (int row = 0; row < cols; ++row)
    {
      free(game_field[row]);
    }
  free(game_field);
  
  return 0; 
}
  
int getRandomNumber(int bound)
{
  return rand() % (bound + 1);
}
 
