#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "./data/game_field.h"

#define bool char
#define TRUE 1
#define FALSE 0

bool if_true_check_if_cell_is_alive(bool condition, char * cell);

int main()
{
  t_game_field * game_field = create_game_field(25, 50);
  int rows = game_field->rows;
  int cols = game_field->cols;

  char ** field = game_field->field;
  int alive_cells = set_alive_cells_random(game_field, 8888);
  
  // Game process
  long milliseconds = 125;
  struct timespec timegap;
  timegap.tv_sec = milliseconds / 1000;
  timegap.tv_nsec = (milliseconds % 1000) * 1000000;

  while (1)
    {
      // Printing the game_field
      for (int row = 0; row < rows; ++row)
	{	 
	  for (int col = 0; col < cols; ++col)
	    {
	      printf("%c", field[row][col]);
	    }

	  printf("\n");
	}
      
      nanosleep(&timegap, NULL);
      system("clear");
      

      // Determine ALIVE_CELLs and DEAD_CELLs in next generation
      unsigned int size = rows * cols;
      char * marked_for_death[size];
      char * marked_for_life[size];
      unsigned int death_mark_count = 0;
      unsigned int life_mark_count = 0;
      
      for (int row = 0; row < rows; ++row)
	{
	  for (int col = 0; col < cols; ++col)
	    {
	      int row_up = row - 1;
	      int row_down = row + 1;
	      int col_right = col + 1;
	      int col_left = col - 1;
	      
	      int alive_neighbour_cells = 0;

	      // Check horizontal and vertical cells
	      alive_neighbour_cells += if_true_check_if_cell_is_alive((row_up >= 0), &field[row_up][col]);
	      alive_neighbour_cells += if_true_check_if_cell_is_alive((row_down < rows), &field[row_down][col]);
	      alive_neighbour_cells += if_true_check_if_cell_is_alive((col_right < cols), &field[row][col_right]);
	      alive_neighbour_cells += if_true_check_if_cell_is_alive((col_left >= 0), &field[row][col_left]);
	      
	      // Check diagonal cells
	      alive_neighbour_cells += if_true_check_if_cell_is_alive((row_up >= 0) && (col_right < cols), &field[row_up][col_right]);
	      alive_neighbour_cells += if_true_check_if_cell_is_alive((row_down < rows) && (col_right < cols), &field[row_down][col_right]);
	      alive_neighbour_cells += if_true_check_if_cell_is_alive((row_down < rows) && (col_left >= 0), &field[row_down][col_left]);
	      alive_neighbour_cells += if_true_check_if_cell_is_alive((row_up >= rows) && (col_left >= 0), &field[row_up][col_left]);
	      
	      // Apply conway's game of life rules
	      if (alive_neighbour_cells == 2)
		{
		  continue;
		}
	      else if (alive_neighbour_cells == 3)
		{
		  marked_for_life[life_mark_count] =  &field[row][col];
		  ++life_mark_count;
		}
	      else if ((alive_neighbour_cells > 3) || (alive_neighbour_cells < 2))
		{
		  marked_for_death[death_mark_count] = &field[row][col];
		  ++death_mark_count;		  
		}	      
	    }
	}

      // Changing the game_field
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

  // TODO: Also need to free the pointer to the game_field type.
  for (int row = 0; row < rows; ++row)
    {
      free(field[row]);
    }
  free(field);
  
  return 0; 
}

bool if_true_check_if_cell_is_alive(bool condition, char * cell)
{
  if (condition)
    {
      return * cell == ALIVE_CELL;
    }

  return FALSE;
}
