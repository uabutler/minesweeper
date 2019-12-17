#include<curses.h>
#include<string.h>
#include<vector>
#include<iostream>

using namespace std;

enum state {gamemenu, load, options, game, quit} STATE;

typedef struct GAME_OPTIONS
{
  unsigned height;
  unsigned width;
  unsigned bombs;
} OPTIONS;

template<typename T>
struct menuItem
{
  string text;
  T value;
};

template<typename T>
struct menu
{
  vector<struct menuItem<T>> items;
  size_t current;
  int height;
  int width;
};

// Rings the bell when the user makes
// and invalid key press
void bell() { cout << "\a"; }

void mainMenu();

int main()
{
  initscr();
  cbreak();
  keypad(stdscr, TRUE);
  noecho();

  STATE = gamemenu;

  while(STATE != quit)
  {
    if(STATE == gamemenu)
      mainMenu();
  }

  endwin();
  return 0;
}

void mainMenu()
{
  struct menu<enum state> mainMenu;

  mainMenu.items =
  {
    {"New Game", options},
    {"Load Game", load},
    {"Quit", quit}
  };

  mainMenu.height = mainMenu.items.size() + 1;

  mainMenu.width = 9; // Initiallized to 4 for the word "Menu"
  for(size_t i = 0; i < mainMenu.items.size(); i++)
    mainMenu.width = max(static_cast<size_t>(mainMenu.width), mainMenu.items[i].text.length() + 1);

  int maxrow, maxcol, row, col;
  getmaxyx(stdscr, maxrow, maxcol);

  row = (maxrow - mainMenu.height) / 2;
  col = (maxcol - mainMenu.width) / 2;

  move(row, col);

  attron(A_STANDOUT);
  printw("MAIN MENU");
  attroff(A_STANDOUT);

  for(size_t i = 0; i < mainMenu.items.size(); i++)
  {
    move(row + i + 1, col + 1);
    printw("%s", mainMenu.items[i].text.c_str());
  }

  mainMenu.current = 0;
  move(row + mainMenu.current + 1, col);
  refresh();

  int input = 0;

  while((input = getch()) != '\n')
  {
    if(input == KEY_UP || input == 'k')
    {
      if(mainMenu.current != 0)
        mainMenu.current--;
      else
        bell();
    }
    else if(input == KEY_DOWN || input == 'j')
    {
      if(mainMenu.current < (mainMenu.items.size() - 1))
        mainMenu.current++;
      else
        bell();
    }
    else
    {
      bell();
    }

    move(row + mainMenu.current + 1, col);
    refresh();
  }

  STATE = mainMenu.items[mainMenu.current].value;
}
