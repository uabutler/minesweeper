#include "main.h"
#include "menu.h"
#include "common.h"

void getOptions(OPTIONS* gameOptions)
{
  // Default options
  OPTIONS easy = {9, 9, 10};
  OPTIONS medium = {16, 16, 40};
  OPTIONS hard = {16, 40, 99};

  // Create the options menu
  Menu<OPTIONS> optionsMenu("Difficulty");

  optionsMenu.addItem("Easy", easy);
  optionsMenu.addItem("Medium", medium);
  optionsMenu.addItem("Hard", hard);

  // Create the return menu
  // presents options to save the settings or cancel
  Menu<state> returnMenu(false);

  returnMenu.addItem("Save", game);
  returnMenu.addItem("Cancel", gamemenu);

  // print both of the menus
  int maxrow, maxcol;
  getmaxyx(stdscr, maxrow, maxcol);

  int height = optionsMenu.getHeight() + returnMenu.getHeight() + 1;
  int width = max(optionsMenu.getWidth(), returnMenu.getWidth());

  int startCol = (maxcol - width) / 2;

  int startOptRow = (maxrow - height) / 2;
  int startRetRow = startOptRow + optionsMenu.getHeight() + 1;

  returnMenu.print(startRetRow, startCol);
  returnMenu.isSelected(false);

  optionsMenu.print(startOptRow, startCol);

  // Get user input for the difficulty menu
  int input;

  while((input = getch()) != '\n')
  {
    bool error = true;
    if(isUp(input))
      error = error && !optionsMenu.prev();
    if(isDown(input))
      error = error && !optionsMenu.next();
    if(error)
      bell();
  }

  *gameOptions = optionsMenu.getCurrent();
  returnMenu.isSelected(true);

  // Ask the user is they way to save or cancel
  while((input = getch()) != '\n')
  {
    bool error = true;
    if(isRight(input))
      error = error && !returnMenu.next();
    if(isLeft(input))
      error = error && !returnMenu.prev();
    if(error)
      bell();
  }

  STATE = returnMenu.getCurrent();

  clear();
}
