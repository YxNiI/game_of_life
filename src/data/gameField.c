#include <stdlib.h>

#include "./gameField.h"

GameField * createGameField(int rows, int cols)
{
  GameField * gameField = (GameField *) malloc(sizeof(GameField));  

  gameField->rows = rows;
  gameField->cols = cols;

  gameField->field = (char **) malloc(rows * (sizeof(char *)));
  char ** field = gameField->field;
  for (int row = 0; row < rows; ++row)
    {
      field[row] = (char *) malloc(cols * sizeof(char));

      for (int col = 0; col < cols; ++col)
	{
	  field[row][col] = DEAD_CELL;
	}      
    }

  setRandomCellsAlive(gameField);

  return gameField;
}

void destroy(GameField *  gameField)
{
  char ** field = gameField->field;
  
  for (int row = 0; row < gameField->rows; ++row)
    {
      free(field[row]);
    }
  free(field);

  free(gameField);
}

static void setRandomCellsAlive(GameField * gameField)
{
  unsigned int rows = gameField->rows;
  unsigned int cols = gameField->cols;
  
  unsigned int rowCellPlacementStart = rows / 4;
  unsigned int rowCellPlacementEnd = rowCellPlacementStart + (rows / 2);
  unsigned int colCellPlacementStart = cols / 4;
  unsigned int colCellPlacementEnd = colCellPlacementStart + (cols / 2);
  
  srand(8787);
  unsigned int aliveCells = 0;

  for (unsigned int row = rowCellPlacementStart; row < rowCellPlacementEnd; ++row)
    {
      for (unsigned int col = colCellPlacementStart; col < colCellPlacementEnd; ++col)
	{
	  unsigned int randomTrueOrFalse = rand() % (1 + 1);
	  
	  if (randomTrueOrFalse)
	    {
	      gameField->field[row][col] = ALIVE_CELL;
	      ++aliveCells;
	    }
	}
    }
}
