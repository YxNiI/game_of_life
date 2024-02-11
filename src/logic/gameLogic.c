#include "./gameLogic.h"
#include "../data/gameField.h"

static bool isAlive(char * cell);

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

	  bool rowUpInBounds = rowUp >= 0;
	  bool rowDownInBounds = rowDown < rows;
	  bool colRightInBounds = colRight < cols;
	  bool colLeftInBounds = colLeft >= 0;
	      
	  int aliveNeighbourCells = 0;

	  // Check horizontal and vertical cells	  
	  if (rowUpInBounds && isAlive(&field[rowUp][col]))
	    {
	      ++aliveNeighbourCells;
	    }
	  if (rowDownInBounds && isAlive(&field[rowDown][col]))
	    {
	      ++aliveNeighbourCells;
	    }
	  if (colRightInBounds && isAlive(&field[row][colRight]))
	    {
	      ++aliveNeighbourCells;
	    }
	  if (colLeftInBounds && isAlive(&field[row][colLeft]))
	    {
	      ++aliveNeighbourCells;
	    }
	      
	  // Check diagonal cells
	  if ((rowUpInBounds && colRightInBounds) && isAlive(&field[rowUp][colRight]))
	    {
	      ++aliveNeighbourCells;
	    }
	  if ((rowDownInBounds && colRightInBounds) && isAlive(&field[rowDown][colRight]))
	    {
	      ++aliveNeighbourCells;
	    }
	  if ((rowDownInBounds && colLeftInBounds) && isAlive(&field[rowDown][colLeft]))
	    {
	      ++aliveNeighbourCells;
	    }
	  if ((rowUpInBounds && colLeftInBounds) && isAlive(&field[rowUp][colLeft]))
	    {
	      ++aliveNeighbourCells;
	    }
	      
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

static bool isAlive(char * cell)
{
  return * cell == ALIVE_CELL;
}
