#include "timer.h"

Timer::Timer(unsigned a):
running(true), attr(a) {}

void Timer::printHelper()
{
  int y, x;
  getyx(stdscr, y, x);

  attrset(attr);
  mvprintw(row, col, "%02d:%02d:%02d",
    time.hours, time.minutes, time.seconds);

  move(y, x);
  refresh();

  attrset(A_NORMAL);
}

void Timer::ThreadMain()
{
  // Start time stays the same
  auto startTime = chrono::steady_clock::now();
  // These will store the duration
  auto prevTime = chrono::steady_clock::now() - startTime;
  auto currentTime = prevTime;

  while(running)
  {
    currentTime = chrono::steady_clock::now() - startTime;

    if(currentTime != prevTime)
    {
      // casts duration to seconds
      auto sec = chrono::duration_cast<chrono::seconds>(currentTime);

      // update the time and print the values
      time.hours = sec.count() / 3600;
      time.minutes = (sec.count() / 60) % 60;
      time.seconds = sec.count() % 60;

      printHelper();

      prevTime = currentTime;
    }
  }
}

void Timer::print(int r, int c)
{
  row = r;
  col = c;
  
  time.hours = time.minutes = time.seconds = 0;
  printHelper();
}

void Timer::start()
{
  clockThread = thread(&Timer::ThreadMain, this);
}

elapsedTime Timer::getElapsedTime()
{
  return time;
}

void Timer::stop()
{
  running = false;
  clockThread.join();
}
