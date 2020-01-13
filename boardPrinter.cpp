#include <ncurses.h>

#include "board.h"
#include "boardPrinter.h"

#define TOP "---"
#define SIDE "|"
#define INTER "+"

#define ETOP "   "
#define ESIDE " "
#define EINTER " "

inline bool BoardPrinter::isInBounds(size_t r, size_t c)
{
  return r > 0 && r < board.getHeight() && c > 0 && c < board.getWidth();
}

BoardPrinter::BoardPrinter(MinesweeperBoard& b): board(b)
{
  height = (board.getHeight() * 2) + 1;
  width = (board.getWidth() * 4) + 1; 
}

int BoardPrinter::getHeight()
{
  return height;
}

int BoardPrinter::getWidth()
{
  return width;
}

void BoardPrinter::getHeightWidth(int& h, int& w)
{
  h = height;
  w = width;
}

char BoardPrinter::getCenter(size_t r, size_t c)
{
  if(!board.getInit() || !board.isRevealed(r, c))
    return '.';
  if(board.getNum(r, c) == 0)
    return ' ';
  if(board.checkSquare(r, c))
    return 'X';
  
  return board.getNum(r, c) + '0';
}

void BoardPrinter::printHelper()
{
  // Print middles
  for(size_t r = 0; r < board.getHeight(); r++)
  {
    for(size_t c = 0; c < board.getWidth(); c++)
      mvprintw((2 * r) + 1 + row, (4 * c) + 2 + col, "%c", getCenter(r, c));
  }

  // Print sides
  for(size_t r = 0; r < board.getHeight(); r++)
  {
    for(size_t c = 0; c < (board.getWidth() - 1); c++)
    {
      if(!board.isRevealed(r, c) || !board.isRevealed(r, c + 1))
        mvprintw((2 * r) + 1 + row, (4 * c) + 4 + col, SIDE);
      else
        mvprintw((2 * r) + 1 + row, (4 * c) + 4 + col, ESIDE);
    }
  }

  // Print top and bottom
  for(size_t r = 0; r < (board.getHeight() - 1); r++)
  {
    for(size_t c = 0; c < board.getWidth(); c++)
    {
      if(!board.isRevealed(r, c) || !board.isRevealed(r + 1, c))
        mvprintw((2 * r) + 2 + row, (4 * c) + 1 + col, TOP);
      else
        mvprintw((2 * r) + 2 + row, (4 * c) + 1 + col, ETOP);
    }
  }

  // Print intersections
  for(size_t r = 0; r < (board.getHeight() - 1); r++)
  {
    for(size_t c = 0; c < (board.getWidth() - 1); c++)
    {
      if(!board.isRevealed(r, c) || !board.isRevealed(r + 1, c) ||
        !board.isRevealed(r, c + 1) || !board.isRevealed(r + 1, c + 1))
        mvprintw((2 * r) + 2 + row, (4 * col) + 4 + col, INTER);
      else
        mvprintw((2 * r) + 2 + row, (4 * col) + 4 + col, INTER);
    }
  }
}

void BoardPrinter::print(int r, int c)
{
  int i;
  row = r;
  col = c;

  // Print top
  move(row, col);

  for(i = 0; i < board.getWidth(); i++)
    printw(INTER TOP); 

  printw(INTER);

  // Print sides
  for(i = row + 1; i < (2 * board.getHeight()) + (row + 1); i += 2)
  {
    mvprintw(i, col, SIDE);
    mvprintw(i + 1, col, INTER);

    mvprintw(i, col + (width - 1), SIDE);
    mvprintw(i + 1, col + (width - 1), INTER);
  }

  // Print bottom
  move(i - 1, col);

  for(i = 0; i < board.getWidth(); i++)
    printw(INTER TOP);

  update(0, 0);
}

void BoardPrinter::update(int r, int c)
{
  printHelper();

  moveCursor(r, c);

  refresh();
}

void BoardPrinter::moveCursor(int r, int c)
{
  move((2 * r) + 1 + row, (4 * c) + 2 + col);
  refresh();
}
