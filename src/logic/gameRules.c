#include "./gameRules.h"
#include "../data/gameField.h"

void iterateGeneration(GameField * gameField)
{
  int rows = gameField->rows;
  int cols = gameField->cols;
  char ** field = gameField->field;
  
  unsigned int size = rows * cols;
  char * markedForDeath[size];
  char * markedForLife[size];
  unsigned int deathMarkCount = 0;
  unsigned int lifeMarkCount = 0;
      
  for (int row = 0; row < rows; ++row)
    {
      for (int col = 0; col < cols; ++col)
	{
	  int rowUp = row - 1;
	  int rowDown = row + 1;
	  int colRight = col + 1;
	  int colLeft = col - 1;
	      
	  int aliveNeighbourCells = 0;

	  // Check horizontal and vertical cells
	  aliveNeighbourCells += ifTrueCheckIfCellIsAlive((rowUp >= 0), &field[rowUp][col]);
	  aliveNeighbourCells += ifTrueCheckIfCellIsAlive((rowDown < rows), &field[rowDown][col]);
	  aliveNeighbourCells += ifTrueCheckIfCellIsAlive((colRight < cols), &field[row][colRight]);
	  aliveNeighbourCells += ifTrueCheckIfCellIsAlive((colLeft >= 0), &field[row][colLeft]);
	      
	  // Check diagonal cells
	  aliveNeighbourCells += ifTrueCheckIfCellIsAlive((rowUp >= 0) && (colRight < cols), &field[rowUp][colRight]);
	  aliveNeighbourCells += ifTrueCheckIfCellIsAlive((rowDown < rows) && (colRight < cols), &field[rowDown][colRight]);
	  aliveNeighbourCells += ifTrueCheckIfCellIsAlive((rowDown < rows) && (colLeft >= 0), &field[rowDown][colLeft]);
	  aliveNeighbourCells += ifTrueCheckIfCellIsAlive((rowUp >= rows) && (colLeft >= 0), &field[rowUp][colLeft]);
	      
	  // Apply conway's game of life rules
	  if (aliveNeighbourCells == 2)
	    {
	      continue;
	    }
	  else if (aliveNeighbourCells == 3)
	    {
	      markedForLife[lifeMarkCount] =  &field[row][col];
	      ++lifeMarkCount;
	    }
	  else if ((aliveNeighbourCells > 3) || (aliveNeighbourCells < 2))
	    {
	      markedForDeath[deathMarkCount] = &field[row][col];
	      ++deathMarkCount;		  
	    }	      
	}
    }

  // Changing the gameField
  for (unsigned int index = 0; index < deathMarkCount; ++index)
    {
      * markedForDeath[index] = DEAD_CELL;
    }

  for (unsigned int index = 0; index < lifeMarkCount; ++index)
    {
      * markedForLife[index] = ALIVE_CELL;
    }

}

static bool ifTrueCheckIfCellIsAlive(bool condition, char * cell)
{
  if (condition)
    {
      return * cell == ALIVE_CELL;
    }

  return FALSE;
}
