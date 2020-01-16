#ifndef BOARD_H
#define BOARD_H

#include <vector>

using namespace std;

class MinesweeperBoard
{
private:
  vector<vector<bool>> bombLocations;
  vector<vector<bool>> revealed;
  vector<vector<unsigned>> surround;
  vector<vector<bool>> flagged;

  size_t height;
  size_t width;
  unsigned bombs;

  bool isInit;

  void placeBombs(size_t r, size_t c);

  inline unsigned computeSurroundHelper(size_t r, size_t c);
  void computeSurround();

public:
  MinesweeperBoard(size_t h, size_t w, unsigned b);

  size_t getHeight();
  size_t getWidth();
  
  void init(size_t r, size_t c);
  bool getInit();
  bool isRevealed(size_t r, size_t c);
  unsigned getNum(size_t r, size_t c);
  bool checkSquare(size_t r, size_t c);
  void reveal(size_t r, size_t c);
  bool checkWin();
  void putFlag(size_t r, size_t c);
  void rmFlag(size_t r, size_t c);
  void toggleFlag(size_t r, size_t c);
  bool getFlag(size_t r, size_t c);
};

#endif // BOARD_H
