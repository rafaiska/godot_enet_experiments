#ifndef _map_h_
#define _map_h_

#include <cstdint>
#include <stdint.h>

namespace rapinae {
class SMap {
private:
  uint32_t w;
  uint32_t h;

public:
  SMap(uint32_t w, uint32_t h) {
    this->h = h;
    this->w = w;
  }

  uint32_t get_w() const { return this->w; }
  uint32_t get_h() const { return this->h; }
};
} // namespace rapinae

#endif