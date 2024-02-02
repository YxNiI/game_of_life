#include <stdio.h>
#include <stdlib.h>

#define BOOL char
#define FALSE 0
#define TRUE 1

/*
 * 1. Jede Zelle mit weniger als zwei lebenden Nachbarn stirbt.
 * 2. Jede Zelle mit zwei oder drei Nachbarn lebt weiter, zur nächsten Generation.
      - Jede Iteration ist eine Generation.
 * 3. Jede Zelle mit mehr als drei Nachbarn stirbt.
 * 4. Jede Zelle mit exakt drei Nachbarn erwacht zum Leben.
 */

int getRandomNumber(unsigned int bound);

int main()
{
  unsigned int rows = 50;
  unsigned int cols = 50;
  char ** game_field = (char **) malloc(rows * sizeof(char *));

  for (unsigned int y = 0; y < cols; ++y)
    {
      game_field[y] = (char *) malloc(cols * sizeof(char));
    }

  for (unsigned int y = 0; y < rows; ++y)
    {
      for (unsigned int x = 0; x < cols; ++x)
	{
	  game_field[y][x] = ' ';	
	}
    }

  BOOL active_life = TRUE;

  unsigned int alive_cells = 50;

  srand(4242);

  for (unsigned int y = 0; y < alive_cells; ++y)
    {
      game_field[getRandomNumber(alive_cells)][getRandomNumber(alive_cells)] = 'X';
    }

  while (alive_cells)
    {
      for (unsigned int y = 0; y < rows; ++y)
	{
	  for (unsigned int x = 0; x < cols; ++x)
	    {
	      unsigned int alive_neighbour_cells = 0;
	      
	    }
	}
    }

  BOOL active_life = TRUE;

  unsigned int alive_cells = 50;

  srand(4242);

  for (unsigned int y = 0; y < alive_cells; ++y)
    {
      game_field[getRandomNumber(alive_cells)][getRandomNumber(alive_cells)] = 'X';
    }

  while (alive_cells)
    {
        for (unsigned int y = 0; y < rows; ++y)
	  {
	    for (unsigned int x = 0; x < cols; ++x)
	      {
		unsigned int alive_neighbour_cells = 0;

		unsigned int row_up = y + 1;
		unsigned int row_down = y - 1;
		unsigned int col_right = x + 1;
		unsigned int col_left = x - 1;

		if (row_up >= 0)
		  {
		    game_field[row_up][x]
		  }
	      }
	  }

	for (unsigned int y = 0; y < rows; ++y)
	  {
	    for (unsigned int x = 0; x < cols; ++x)
	      {
		printf("%c", game_field[y][x]);
	      }
	  }      

    }
            

  for (unsigned int y = 0; y < rows; ++y)
    {
      for (unsigned int x = 0; x < cols; ++x)
	{
	  printf("%c", game_field[y][x]);
	}
    }
  
  return 0; 
}
  
int getRandomNumber(unsigned int bound)
{
  return rand() % (bound + 1);
} 

void applyToLife(void (* function)())
{
    for (unsigned int y = 0; y < rows; ++y)
    {
      for (unsigned int x = 0; x < cols; ++x)
	{
	  printf("%c", game_field[y][x]);
	}
    }
}
