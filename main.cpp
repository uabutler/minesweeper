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
    {
      curs_set(0);
      mainMenu();
    }
    if(STATE == options)
    {
      curs_set(0);
      getOptions(&gameOptions);
    }
    if(STATE == game)
    {
      curs_set(1);
      playGame(gameOptions);
    }
  }

  endwin();
  return 0;
}
