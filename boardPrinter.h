#ifndef BOARD_PRINTER_H
#define BOARD_PRINTER_H

/*
 * This is a helper class to print the minesweeper board.
 * the board itself is managed by the user, this just prints said
 * board using ncurses
 */

#include <ncurses.h>

#include "main.h"
#include "board.h"

class BoardPrinter
{
private:
  MinesweeperBoard& board;

  int row;
  int col;

  int height;
  int width;

  inline bool isInBounds(size_t r, size_t c);
  char getCenter(size_t r, size_t c);
  void printHelper();

public:
  // First, the constructor is initialized with a reference to the
  // board the user will manage
  BoardPrinter(MinesweeperBoard& b);

  // The height and width of the printed board. This isn't the same
  // as the number of squares on the board
  int getHeight();
  int getWidth();
  void getHeightWidth(int& h, int& w);

  // The initial print of the board at the given coordinates
  void print(int r, int c);
  // Updates the board and moves the cursor to the given coordinates
  void update(int r, int c);
  // Moves the cursor the the given coordinates wihtout updating the
  // whole board
  void moveCursor(int r, int c);
};

#endif // BOARD_PRINTER_H
