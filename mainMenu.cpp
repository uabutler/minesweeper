#include "main.h"
#include "menu.h"
#include "common.h"

void mainMenu()
{
  // Create the menu
  Menu<state> mainMenu("Main Menu");

  // Each item sets the program to a different state if selected
  mainMenu.addItem("New Game", options);
  mainMenu.addItem("Leaderboard", leaderboard);
  mainMenu.addItem("Quit", quit);

  // Print the menu
  int maxrow, maxcol;
  getmaxyx(stdscr, maxrow, maxcol);

  int row = (maxrow - mainMenu.getHeight()) / 2;
  int col = (maxcol - mainMenu.getWidth()) / 2;

  mainMenu.print(row, col);

  // The user can then select an option
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
