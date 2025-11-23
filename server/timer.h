#ifndef _timer_h_
#define _timer_h_

#include <chrono>

namespace rapinae {
class RWTimer {
  using clock = std::chrono::system_clock;
  using time_point_type =
      std::chrono::time_point<clock, std::chrono::milliseconds>;

public:
  RWTimer() { set_start(); }
  void set_start();
  float getElapsedTimeMs();

private:
  time_point_type start;
};
} // namespace rapinae

#endif