#include "actor.h"
#include "attribute.h"
#include "vector.h"
#include <string>

bool rapinae::RWActor::has_attr(std::string name) {
    return attributes.find(name) != attributes.end();
}

double rapinae::RWActor::get_double_attr(std::string name) {
    return attributes.at(name).get_d_value();
}

uint32_t rapinae::RWActor::get_int_attr(std::string name) {
    return attributes.at(name).get_i_value();
}

std::string rapinae::RWActor::get_str_attr(std::string name) {
    return attributes.at(name).get_s_value();
}

void *rapinae::RWActor::get_void_attr(std::string name) {
    return attributes.at(name).get_v_value();
}

void rapinae::RWActor::add_or_update_attr(std::string name, double value) {
    insert_attr_if_does_not_exist(name);
    attributes.at(name).set_d_value(value);
    updated.insert(name);
}

void rapinae::RWActor::add_or_update_attr(std::string name, uint32_t value) {
    insert_attr_if_does_not_exist(name);
    attributes.at(name).set_i_value(value);
    updated.insert(name);
}

void rapinae::RWActor::add_or_update_attr(std::string name, std::string value) {
    insert_attr_if_does_not_exist(name);
    attributes.at(name).set_s_value(value);
    updated.insert(name);
}

void rapinae::RWActor::add_or_update_attr(std::string name, rapinae::Vector2 *value) {
    insert_attr_if_does_not_exist(name);
    attributes.at(name).set_vector2_value(value);
    updated.insert(name);
}

void rapinae::RWActor::insert_attr_if_does_not_exist(std::string name) {
    if (!has_attr(name)) {
        attributes.insert({name, rapinae::RWAttr(name)});
    }
}

std::vector<rapinae::RWAttr> rapinae::RWActor::get_updated_attrs() const {
    std::vector<rapinae::RWAttr> vector;
    vector.reserve(updated.size());
    for (auto &val: updated) {
        vector.push_back(attributes.at(val));
    }
    return vector;
}

std::vector<rapinae::RWAttr> rapinae::RWActor::get_all_attrs() const {
    std::vector<rapinae::RWAttr> vector;
    vector.reserve(attributes.size());
    for (auto &val: attributes) {
        vector.push_back(val.second);
    }
    return vector;
}

void rapinae::RWActor::set_attr_updated(std::string attr_name) {
    attributes.at(attr_name).set_value_changed(true);
}