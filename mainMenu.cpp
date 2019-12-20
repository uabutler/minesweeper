#include "main.h"
#include "menu.h"
#include "common.h"

void mainMenu()
{
  Menu<state> mainMenu("Main Menu");

  mainMenu.addItem("New Game", options);
  mainMenu.addItem("Leaderboard", leaderboard);
  mainMenu.addItem("Quit", quit);

  int maxrow, maxcol;
  getmaxyx(stdscr, maxrow, maxcol);

  int row = (maxrow - mainMenu.getHeight()) / 2;
  int col = (maxcol - mainMenu.getWidth()) / 2;

  mainMenu.print(row, col);

  int input;
  while((input = getch()) != '\n')
  {
    bool error = true;
    if(isUp(input))
      error = error && !mainMenu.prev();
    if(isDown(input))
      error = error && !mainMenu.next();
    if(error)
      bell();
  }

  STATE =  mainMenu.getCurrent();

  clear();
}
