#include "main.h"
#include "mainMenu.h"
#include "common.h"
#include "options.h"

using namespace std;

enum state STATE = gamemenu;

int main()
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
  }

  endwin();
  return 0;
}
