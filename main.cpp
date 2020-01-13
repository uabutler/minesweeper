#include "main.h"
#include "mainMenu.h"
#include "common.h"
#include "options.h"
#include "game.h"

using namespace std;

enum state STATE = gamemenu;

int main(int argc, char** argv)
{
  initscr();
  cbreak();
  keypad(stdscr, TRUE);
  noecho();

  OPTIONS gameOptions;

  while(STATE != quit)
  {
    if(STATE == gamemenu)
      mainMenu();
    if(STATE == options)
      getOptions(&gameOptions); 
    if(STATE == game)
      playGame(gameOptions);
  }

  endwin();
  return 0;
}
