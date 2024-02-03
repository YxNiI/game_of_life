#ifdef _WIN32
#include <conio.h>
#else
#include <stdio.h>
#define clrscr() printf("\e[1;1H\e[2J")
#endif

#include <stdlib.h>
#include <time.h>

int getRandomZeroOrOne();

int main()
{
  const char ALIVE_CELL = 'X';
  const char DEAD_CELL = '_';
  
  // Create game_field
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

  // Initialize game_field
  int alive_cells = 0;

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
	      ++alive_cells;
	    }
	  else
	    {
	      game_field[row][col] = DEAD_CELL;
	    }
	}
    }

  long milliseconds = 125;
  struct timespec timegap;
  timegap.tv_sec = milliseconds / 1000;
  timegap.tv_nsec = (milliseconds % 1000) * 1000000;

  // Game process
  while (1)
    {
      for (int row = 0; row < rows; ++row)
	{	 
	  for (int col = 0; col < cols; ++col)
	    {
	      printf("%c", game_field[row][col]);
	    }

	  printf("\n");
	}

      clrscr();
      nanosleep(&timegap, NULL);
      

      unsigned int size = rows * cols;
      char * marked_for_death[size];
      char * marked_for_life[size];
      unsigned int death_mark_count = 0;
      unsigned int life_mark_count = 0;
      
      for (int row = 0; row < rows; ++row)
	{
	  for (int col = 0; col < cols; ++col)
	    {
	      int alive_neighbour_cells = 0;

	      int row_up = row - 1;
	      int row_down = row + 1;
	      int col_right = col + 1;
	      int col_left = col - 1;

	      // Check horizontal and vertical cells
	      if (row_up >= 0)
		{
		  if (game_field[row_up][col] == ALIVE_CELL)
		    ++alive_neighbour_cells;
		}
	      if (row_down < rows)
		{
		  if (game_field[row_down][col] == ALIVE_CELL)
		    ++alive_neighbour_cells;
		}
	      if (col_right < cols)
		{
		  if (game_field[row][col_right] == ALIVE_CELL)
		    ++alive_neighbour_cells;
		}
	      if (col_left >= 0)
		{
		  if (game_field[row][col_left] == ALIVE_CELL)
		    ++alive_neighbour_cells;
		}

	      // Check diagonal cells
	      if ((row_up >= 0) && (col_right < cols))
		{
		  if (game_field[row_up][col_right] == ALIVE_CELL)
		    ++alive_neighbour_cells;
		}
	      if ((row_down < rows) && (col_right < cols))
		{
		  if (game_field[row_down][col_right] == ALIVE_CELL)
		    ++alive_neighbour_cells;
		}
	      if ((row_down < rows) && (col_left >= 0))
		{
		  if (game_field[row_down][col_left] == ALIVE_CELL)
		    ++alive_neighbour_cells;
		}
	      if ((row_up >= rows) && (col_left >= 0))
		{
		  if (game_field[row_up][col_left] == ALIVE_CELL)
		    ++alive_neighbour_cells;
		}

	      /*
	       * 1. Jede Zelle mit weniger als zwei lebenden Nachbarn stirbt.
	       * 2. Jede Zelle mit zwei oder drei Nachbarn lebt weiter, zur nächsten Generation.
	       - Jede Iteration ist eine Generation.
	       * 3. Jede Zelle mit mehr als drei Nachbarn stirbt.
	       * 4. Jede Zelle mit exakt drei Nachbarn erwacht zum Leben.
	       */

	      // Apply conway's game of life rules
	      if (alive_neighbour_cells < 2)
		{
		  marked_for_death[death_mark_count] = &game_field[row][col];
		  ++death_mark_count;
		}
	      else if (alive_neighbour_cells >= 2 && alive_neighbour_cells <= 3)
		{
		  marked_for_life[life_mark_count] =  &game_field[row][col];
		  ++life_mark_count;
		}
	      else if (alive_neighbour_cells > 3)
		{
		  marked_for_death[death_mark_count] = &game_field[row][col];
		  ++death_mark_count;		  
		}
	      else if (alive_neighbour_cells == 3)
		{
		  marked_for_life[life_mark_count] =  &game_field[row][col];
		  ++life_mark_count;
		}
	    }
	}

      for (unsigned int index = 0; index < death_mark_count; ++index)
	{
	  * marked_for_death[index] = DEAD_CELL;
	  --alive_cells;
	}

      for (unsigned int index = 0; index < life_mark_count; ++index)
	{
	  * marked_for_life[index] = ALIVE_CELL;
	  ++alive_cells;
	}
    }
  
  // Freeing the game_field
  for (int row = 0; row < rows; ++row)
    {
      free(game_field[row]);
    }
  free(game_field);
  
  return 0; 
}
