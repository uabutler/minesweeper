#include <iostream>
#include "board.h"

using namespace std;

int main()
{
  MinesweeperBoard board(20, 20, 20);
  
  board.init(10, 10);

  cout << endl;

  for(size_t i = 0; i < 20; i++)
  {
    for(size_t j = 0; j < 20; j++)
    {
      if(board.checkSquare(i, j))
        cout << "X";
      else
        cout << board.getNum(i, j);
    }

    cout << '\n';
  }

  cout << endl;
}
