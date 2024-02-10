#include <stdio.h>

#include "./consoleView.h"
#include "../data/gameField.h"

void printView(GameField * gameField)
{
  for (int row = 0; row < gameField->rows; ++row)
    {	 
      for (int col = 0; col < gameField->cols; ++col)
	{
	  printf("%c", gameField->field[row][col]);
	}

      printf("\n");
    }
}
