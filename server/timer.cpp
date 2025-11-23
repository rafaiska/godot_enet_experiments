#include "timer.h"

void rapinae::RWTimer::set_start() {
  start = std::chrono::time_point_cast<std::chrono::milliseconds>(clock::now());
}

float rapinae::RWTimer::getElapsedTimeMs() {
  auto end = clock::now();
  return (end - start).count() / 1000000000.0;
}