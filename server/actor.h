#ifndef _actor_h_
#define _actor_h_

#include "attribute.h"
#include "vector.h"
#include <string>
#include <unordered_map>
#include <vector>
#include <unordered_set>

namespace rapinae {
    class RWActor {
        std::unordered_map<std::string, RWAttr> attributes;
        std::unordered_set<std::string> updated;
        std::string id;

        void insert_attr_if_does_not_exist(std::string name);

        public:
            RWActor(std::string _id): id(_id){};
            std::string get_id() const {return id;}
            bool has_attr(std::string name);
            double get_double_attr(std::string name);
            uint32_t get_int_attr(std::string name);
            std::string get_str_attr(std::string name);
            void* get_void_attr(std::string name);
            void add_or_update_attr(std::string name, double value);
            void add_or_update_attr(std::string name, uint32_t value);
            void add_or_update_attr(std::string name, std::string value);
            void add_or_update_attr(std::string name, rapinae::Vector2 *value);
            std::vector<rapinae::RWAttr> get_updated_attrs() const;
            std::vector<rapinae::RWAttr> get_all_attrs() const;
    };
}

#endif