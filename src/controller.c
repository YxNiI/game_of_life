#include <stdlib.h>
#include <time.h>

#include "./data/gameField.h"
#include "./presentation/consoleView.h"
#include "./logic/gameLogic.h"

int main()
{
  GameField * gameField = createGameField(25, 50);
  
  long milliseconds = 125;
  struct timespec timegap;
  timegap.tv_sec = milliseconds / 1000;
  timegap.tv_nsec = (milliseconds % 1000) * 1000000;

  while (1)
    {
      print(gameField);
      
      nanosleep(&timegap, NULL);
      system("clear");
      
      incrementGeneration(gameField);
    }

  destroy(gameField);
  
  return 0; 
}
