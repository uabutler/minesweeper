#include <vector>
#include <random>
#include <chrono>

#include <iostream>

#include "board.h"

inline bool isInBounds(const vector< vector<bool> >& a, size_t r, size_t c)
{
  return r < a.size() && c < a[0].size();
}

// Randomly places bombs on the board, while avoiding placing a bomb
// at the players first choice (given by r, c)
void MinesweeperBoard::placeBombs(size_t r, size_t c)
{
  // Placeholder
  bombLocations[r][c] = true;

  default_random_engine
    rng(std::chrono::system_clock::now().time_since_epoch().count());

  for(size_t i = 0; i < bombs; i++)
  {
    // A uniform chance of being placed at any of the remaining
    // spots
    uniform_int_distribution<size_t>
      rand(0, (bombLocations.size()*bombLocations[0].size()) - (i + 1));

    // Count how many empty slots we should pass before we place
    // the bomb
    size_t count = rand(rng);
    
    size_t row = 0, col = 0;
    size_t index = 0;

    while(count)
    {
      row = index % bombLocations.size();
      col = index / bombLocations.size();

      if(!bombLocations[row][col])
        count--;

      index++;
    }

    // Place the bomb
    bombLocations[row][col] = true;
  }

  // Remove placeholder
  bombLocations[r][c] = false;
}

// Computes the number of bombs surrounding a single place while
// avoiding going out of bounds
inline unsigned MinesweeperBoard::computeSurroundHelper(size_t r, size_t c)
{
  if(bombLocations[r][c]) return 9;

  unsigned count = 0;

  for(size_t i = (r ? (r - 1) : 0); i <= r + 1; i++)
  {
    for(size_t j = (c ? (c - 1) : 0); j <= c + 1; j++)
    {
      if(isInBounds(bombLocations, i, j))
        if(bombLocations[i][j]) count++;
    }
  }

  return count - (bombLocations[r][c] ? 1 : 0);
}

// Computes the number of bombs surrounding each square
void MinesweeperBoard::computeSurround()
{
  for(size_t i = 0; i < surround.size(); i++)
  {
    for(size_t j = 0; j < surround[0].size(); j++)
      surround[i][j] = computeSurroundHelper(i, j);
  }
}

// Constructor
MinesweeperBoard::MinesweeperBoard(size_t h, size_t w, unsigned b):
height(h), width(w), bombs(b), isInit(false)
{
  bombLocations = vector< vector<bool> >(h, vector<bool>(w, false));
  revealed = vector< vector<bool> >(h, vector<bool>(w, false));
  flagged = vector< vector<bool> >(h, vector<bool>(w, false));
  surround = vector< vector<unsigned> >(h, vector<unsigned>(w, 0));
}

// Getters
size_t MinesweeperBoard::getHeight()
{
  return height;
}

size_t MinesweeperBoard::getWidth()
{
  return width;
}

// Initialized the board after the first move, given by r, c
void MinesweeperBoard::init(size_t r, size_t c)
{
  placeBombs(r, c);
  computeSurround();

  isInit = true;
}

// Has the board been initialized?
bool MinesweeperBoard::getInit()
{
  return isInit;
}

// Has this square been revealed
bool MinesweeperBoard::isRevealed(size_t r, size_t c)
{
  return revealed[r][c];
}

// Get the number of bombs surrounding a given square
unsigned MinesweeperBoard::getNum(size_t r, size_t c)
{
  return surround[r][c];
}

// Check to see if a square has a bomb
bool MinesweeperBoard::checkSquare(size_t r, size_t c)
{
  return bombLocations[r][c];
}

// This method reveals a sqaure, but doesn't have the overhead of
// creating and returning the list
void MinesweeperBoard::reveal(size_t r, size_t c)
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


bool MinesweeperBoard::checkWin()
{
  for(size_t i = 0; i < height; i++)
  {
    for(size_t j = 0; j < width; j++)
    {
      if(revealed[i][j] == bombLocations[i][j])
        return false;
    }
  }
  
  return true;
}

void MinesweeperBoard::putFlag(size_t r, size_t c)
{
  flagged[r][c] = true;
}

void MinesweeperBoard::rmFlag(size_t r, size_t c)
{
  flagged[r][c] = false;
}

void MinesweeperBoard::toggleFlag(size_t r, size_t c)
{
  flagged[r][c] = flagged[r][c] != true;
}

bool MinesweeperBoard::getFlag(size_t r, size_t c)
{
  return flagged[r][c];
}
