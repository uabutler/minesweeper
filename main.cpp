#include "main.h"
#include "menu.h"
#include "common.h"

using namespace std;

enum state STATE = gamemenu;

int main()
{
  initscr();
  cbreak();
  keypad(stdscr, TRUE);
  noecho();

  while(STATE != quit)
  {
    if(STATE == gamemenu)
      mainMenu();
  }

  endwin();
  return 0;
}
