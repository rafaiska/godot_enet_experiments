#include "attribute.h"
#include "vector.h"
#include <cstdlib>

rapinae::RWAttr::RWAttr(std::string name) {
  this->name = name;
  type = ATTR_TYPE_NONE;
  v_value = nullptr;
}

void rapinae::RWAttr::set_d_value(double _d_value) {
  d_value = _d_value;
  type = ATTR_TYPE_DOUBLE;
  value_changed = true;
}

void rapinae::RWAttr::set_i_value(int32_t _i_value) {
  i_value = _i_value;
  type = ATTR_TYPE_DOUBLE;
  value_changed = true;
}

void rapinae::RWAttr::set_s_value(std::string &_s_value) {
  s_value = _s_value;
  type = ATTR_TYPE_STRING;
  value_changed = true;
}

void rapinae::RWAttr::set_vector2_value(rapinae::Vector2 *vector2) {
  v_value = vector2;
  type = ATTR_TYPE_VECTOR2;
  value_changed = true;
}