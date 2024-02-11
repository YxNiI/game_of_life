#include "./gameLogic.h"
#include "../data/gameField.h"

static bool isAlive(char * cell);
static void incrementIfTrue(bool condition, int * var);
static void setAndIncrement(char ** array, char * address, unsigned int * index);
static void set(char ** array, char newData, unsigned int numberOfSets);

void incrementGeneration(GameField * gameField)
{
  int rows = gameField->rows;
  int cols = gameField->cols;
  char ** field = gameField->field;
  
  unsigned int size = rows * cols;
  char * deathMarkArray[size];
  char * lifeMarkArray[size];
  unsigned int deathMarkIndex = 0;
  unsigned int lifeMarkIndex = 0;
      
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
	  incrementIfTrue((rowUpInBounds &&
			   isAlive(&field[rowUp][col])),
			  &aliveNeighbourCells);
	  incrementIfTrue((rowDownInBounds &&
			   isAlive(&field[rowDown][col])),
			  &aliveNeighbourCells);
	  incrementIfTrue((colRightInBounds &&
			   isAlive(&field[row][colRight])),
			  &aliveNeighbourCells);
	  incrementIfTrue((colLeftInBounds &&
			   isAlive(&field[row][colLeft])),
			  &aliveNeighbourCells);	  
	      
	  // Check diagonal cells
	  incrementIfTrue(((rowUpInBounds && colRightInBounds) &&
			   isAlive(&field[rowUp][colRight])),
			  &aliveNeighbourCells);
	  incrementIfTrue(((rowDownInBounds && colRightInBounds) &&
			   isAlive(&field[rowDown][colRight])),
			  &aliveNeighbourCells);
	  incrementIfTrue(((rowDownInBounds && colLeftInBounds) &&
			   isAlive(&field[rowDown][colLeft])),
			  &aliveNeighbourCells);
	  incrementIfTrue(((rowUpInBounds && colLeftInBounds) &&
			   isAlive(&field[rowUp][colLeft])),
			  &aliveNeighbourCells);
	 
	  char * currentAddress = &field[row][col];
	  if (aliveNeighbourCells == 2)
	    {
	      continue;
	    }
	  else if (aliveNeighbourCells == 3)
	    {	      
	      setAndIncrement(lifeMarkArray, currentAddress, &lifeMarkIndex);
	    }
	  else if ((aliveNeighbourCells > 3) || (aliveNeighbourCells < 2))
	    {	      
	      setAndIncrement(deathMarkArray, currentAddress, &deathMarkIndex);
	    }
	}
    }
  
  set(deathMarkArray, DEAD_CELL, deathMarkIndex);
  set(lifeMarkArray, ALIVE_CELL, lifeMarkIndex);
}

static bool isAlive(char * cell)
{
  return * cell == ALIVE_CELL;
}

static void incrementIfTrue(bool condition, int * var)
{
  if (condition)
    {
      ++(* var);
    }
}

static void setAndIncrement(char ** array, char * newData, unsigned int * index)
{
  array[(* index)] = newData;
  ++(* index);
}

static void set(char ** array, char newData, unsigned int numberOfSets)
{
  for (unsigned int index = 0; index < numberOfSets; ++index)
    {
      * array[index] = newData;
    }
}
