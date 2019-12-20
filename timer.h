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
  Timer(unsigned a = A_NORMAL);

  void print(int r, int c);

  void start();
  elapsedTime getElapsedTime();
  void stop();
};
