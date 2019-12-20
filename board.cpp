#include <vector>
#include <random>
#include <chrono>

#include "board.h"

bool isInBounds(const vector< vector<bool> >& a, size_t r, size_t c)
{
  return (r > 0 && r < a.size() && c > 0 && c < a[0].size());
}

void placeBombs(vector< vector<bool> >& board, size_t bombs)
{
  default_random_engine
    rng(std::chrono::system_clock::now().time_since_epoch().count());

  for(size_t i = 0; i < bombs; i++)
  {
    uniform_int_distribution<size_t>
      rand(0, (board.size()*board[0].size()) - i);

    size_t count = rand(rng);
    
    size_t row, col;
    size_t index = 0;

    while(count)
    {
      row = index % board.size();
      col = index / board.size();

      if(!board[row][col])
        count--;

      index++;
    }
    board[row][col] = true;
  }
}

unsigned computeSurroundHelper(const vector< vector<bool> >& board,
  size_t row, size_t col)
{
  unsigned count = 0;
  for(int i = (int)row - 1; i <= (int)row + 1; i++)
  {
    for(int j = (int)col - 1; j <= (int)col + 1; j++)
    {
      if(isInBounds(board, i, j))
        if(board[i][j]) count++;
    }
  }

  return count - (board[row][col] ? 1 : 0);
}

void computeSurround(const vector< vector<bool> >& board,
  vector< vector<unsigned> >& surround)
{
  for(size_t i = 0; i < surround.size(); i++)
  {
    for(size_t j = 0; j < surround[0].size(); j++)
      surround[i][j] = computeSurroundHelper(board, i, j);
  }
}

MinesweeperBoard::MinesweeperBoard(size_t h, size_t w, unsigned b):
height(h), width(w), bombs(b)
{
  bombLocations = vector< vector<bool> >(h, vector<bool>(w, false));
  revealed = vector< vector<bool> >(h, vector<bool>(w, false));
  surround = vector< vector<unsigned> >(h, vector<unsigned>(w, 0));
  placeBombs(bombLocations, bombs);
  computeSurround(bombLocations, surround);
}

bool MinesweeperBoard::isRevealed(size_t r, size_t c)
{
  return revealed[r][c];
}

unsigned MinesweeperBoard::getNum(size_t r, size_t c)
{
  return surround[r][c];
}

bool MinesweeperBoard::checkSquare(size_t r, size_t c)
{
  return bombLocations[r][c];
}

vector< pair<size_t, size_t> >
  MinesweeperBoard::reveal(size_t r, size_t c)
{
  vector< pair<size_t, size_t> > out;

  if(!revealed[r][c])
  {
    out.emplace_back(r, c);
    revealed[r][c] = true;
  }
  
  if(surround[r][c] == 0)
  {
    for(int i = (int)r - 1; i <= (int)r + 1; i++)
    {
      for(int j = (int)c - 1; j <= (int)c + 1; j++)
      {
        if(isInBounds(revealed, i, j) && !revealed[i][j])
        {
          auto tmp = reveal(i, j);
          out.insert(out.end(), tmp.begin(), tmp.end());
        }
      }
    }
  }

  return out;
}

void MinesweeperBoard::dumbReveal(size_t r, size_t c)
{
  revealed[r][c] = true;
  
  if(surround[r][c] == 0)
  {
    for(int i = (int)r - 1; i <= (int)r + 1; i++)
    {
      for(int j = (int)c - 1; j <= (int)c + 1; j++)
      {
        if(isInBounds(revealed, i, j) && !revealed[i][j])
          reveal(i, j);
      }
    }
  }
}

