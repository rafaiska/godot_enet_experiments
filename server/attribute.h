#ifndef _attribute_h_
#define _attribute_h_

#include "vector.h"
#include <cstdint>
#include <string>

namespace rapinae {

enum RWAttrType {
  ATTR_TYPE_NONE,
  ATTR_TYPE_DOUBLE,
  ATTR_TYPE_INT,
  ATTR_TYPE_STRING,
  ATTR_TYPE_VECTOR2
};

class RWAttr {
private:
  std::string name;
  RWAttrType type;
  double d_value;
  uint32_t i_value;
  std::string s_value;
  void *v_value;
  bool value_changed;

public:
  RWAttr(std::string name);

  void set_value_changed(bool _changed) {value_changed = _changed;}
  void set_d_value(double _d_value);
  void set_i_value(int32_t _i_value);
  void set_s_value(std::string &_s_value);
  void set_vector2_value(rapinae::Vector2 *vector2);

  std::string get_name() const { return name; }
  RWAttrType get_type() const { return type; }
  double get_d_value() const { return d_value; }
  uint32_t get_i_value() const { return i_value; }
  std::string get_s_value() const { return s_value; }
  void *get_v_value() const { return v_value; }
};

} // namespace rapinae

#endif