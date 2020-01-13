#include <cstring>
#include <ncurses.h>

#include "main.h"
#include "common.h"

bool isMovement(int input);
bool moveGameCursor(int input, BoardPrinter& printer,
  size_t& r, size_t& c);

void game(OPTIONS options)
{
  MinesweeperBoard board(options.height, options.width, options.bombs);

  BoardPrinter printer(board);

  int maxrow, maxcol;
  getmaxyx(maxrow, maxcol);

  int row = (maxrow - printer.getHeight() + 1) / 2;
  int col = (maxcol - printer.getWidth()) / 2;

  if(row < 0 || col < 0)
  {
    char* msg = "Error: Not enough space to print board, \
      press any key to continue";

    mvprintw(maxrow / 2, (maxcol - strlen(msg)) / 2, "%s", msg);

    STATE = options;

    getch();
    clear();
    return;
  }

  printer.print(row, col);

  int curRow = 0;
  int curCol = 0;

  // Wait to initialize board
  int input;
  while((input = getch()) == '\n')
  {
    if(!moveGameCursor(input, printer, board, curRow, curCol))
      bell();
  }

  board.init(curRow, curCol);
}
