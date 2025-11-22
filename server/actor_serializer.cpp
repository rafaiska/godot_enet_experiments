#include "actor_serializer.h"
#include "actor.h"
#include "attribute.h"
#include "vector.h"

#include <nlohmann/json.hpp>
#include <vector>

using json = nlohmann::json;

json d_to_json(const double &value) { return json(value); }
json i_to_json(const int &value) { return json(value); }
json s_to_json(const std::string &value) { return json(value); }

json vec2_to_json(const rapinae::Vector2 *value) { 
    return json({{"x", value->x}, {"y", value->y}});
}

std::string rapinae::serialize_to_json(const rapinae::RWActor &actor, const bool only_updated_attrs) {
    json output;
    output["id"] = actor.get_id();
    std::vector<rapinae::RWAttr> attributes;
    if (only_updated_attrs) attributes = actor.get_updated_attrs();
    else attributes = actor.get_all_attrs();

    for (rapinae::RWAttr attr: attributes) {
        switch (attr.get_type()) {
            case rapinae::ATTR_TYPE_NONE: output[attr.get_name()] = json(); break;
            case rapinae::ATTR_TYPE_DOUBLE: output[attr.get_name()] = d_to_json(attr.get_d_value()); break;
            case rapinae::ATTR_TYPE_INT: output[attr.get_name()] = i_to_json(attr.get_i_value()); break;
            case rapinae::ATTR_TYPE_STRING: output[attr.get_name()] = s_to_json(attr.get_s_value()); break;
            case rapinae::ATTR_TYPE_VECTOR2: output[attr.get_name()] = vec2_to_json((rapinae::Vector2*)attr.get_v_value()); break;
            }
    }

    return output.dump();
}