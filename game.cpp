#include <cstring>
#include <ncurses.h>

#include "main.h"
#include "board.h"
#include "boardPrinter.h"
#include "common.h"

bool isMovement(int input);
bool moveGameCursor(int input, BoardPrinter& printer,
  MinesweeperBoard& board, int& r, int& c);

void playGame(OPTIONS gameOptions)
{
  MinesweeperBoard board(gameOptions.height, gameOptions.width, gameOptions.bombs);

  BoardPrinter printer(board);

  int maxrow, maxcol;
  getmaxyx(stdscr, maxrow, maxcol);

  int row = (maxrow - printer.getHeight() + 1) / 2;
  int col = (maxcol - printer.getWidth()) / 2;

  if(row < 0 || col < 0)
  {
    const char* msg = "Error: Not enough space to print board, "
      "press any key to continue";

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
  while((input = getch()) != '\n')
  {
    if(!moveGameCursor(input, printer, board, curRow, curCol))
      bell();
  }

  board.init(curRow, curCol);
  board.reveal(curRow, curCol);
  printer.update(curRow, curCol);

  // Flag to determine if the game is still going
  bool flag = false;
  while(!flag)
  {
    while((input = getch()) != '\n')
    {
      if(!moveGameCursor(input, printer, board, curRow, curCol))
        bell();
      if(input == 'f' || input == 'F')
      {
        board.toggleFlag(curRow, curCol);
        printer.update(curRow, curCol);
      }
    }

    if(!board.getFlag(curRow, curCol))
    {
      board.reveal(curRow, curCol);
      printer.update(curRow, curCol);
    }
    else
    {
      bell();
    }

    flag = board.checkWin();
  }

  STATE = gamemenu;
}

bool isMovement(int input)
{
  return isUp(input) || isDown(input) ||
    isRight(input) || isLeft(input);
}

bool moveGameCursor(int input, BoardPrinter& printer,
  MinesweeperBoard& board, int& r, int& c)
{
  if(!isMovement(input))
    return false;

  size_t row = r;
  size_t col = c;

  if(isUp(input))
    row--;
  if(isDown(input))
    row++;
  if(isLeft(input))
    col--;
  if(isRight(input))
    col++;

  if(row < board.getHeight() && col < board.getWidth())
  {
    r = row;
    c = col;

    printer.moveCursor(r, c);

    return true;
  }
  else
  {
    return false;
  }
}
