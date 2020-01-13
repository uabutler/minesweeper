#ifndef TIMER_H
#define TIMER_H

#include <thread>
#include <chrono>
#include <ncurses.h>

using namespace std;

typedef struct elapsedTime
{
  unsigned hours;
  unsigned minutes;
  unsigned seconds;
} elapsedTime;

class Timer
{
private:
  thread clockThread;
  void ThreadMain();

  void printHelper();

  bool running;

  int row;
  int col;
  unsigned attr;

  elapsedTime time;

public:
  // The argument is attribute the timer should be printed with
  Timer(unsigned a = A_NORMAL);

  // Puts the time on the screen at the given location
  void print(int r, int c);

  // Starts the timer. This is done asycronously on a seperate thread.
  void start();
  // This gets the amount of time currently displayed on the timer
  elapsedTime getElapsedTime();
  // This stops the thread which leaves the timer with the time it
  // had last time it was updated
  void stop();
};

#endif // TIMER_H
