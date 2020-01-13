#ifndef MAIN_H
#define MAIN_H

#include <curses.h>
#include <iostream>

using namespace std;

// The current state of the game
typedef enum state {gamemenu, leaderboard, options, game, quit} state;
extern state STATE;

// The dimensions of the squares in the game and how many bombs are
// included
typedef struct OPTIONS
{
  unsigned height;
  unsigned width;
  unsigned bombs;
} OPTIONS;

#endif // MAIN_H
