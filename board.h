#include <vector>

using namespace std;

class MinesweeperBoard
{
private:
  vector< vector<bool> > bombLocations;
  vector< vector<bool> > revealed;
  vector< vector<unsigned> > surround;

  size_t height;
  size_t width;
  unsigned bombs;

public:
  MinesweeperBoard(size_t h, size_t w, unsigned b);
  
  bool isRevealed(size_t r, size_t c);
  unsigned getNum(size_t r, size_t c);
  bool checkSquare(size_t r, size_t c);
  vector< pair<size_t, size_t> > reveal(size_t r, size_t c);
  void dumbReveal(size_t r, size_t c);
};
