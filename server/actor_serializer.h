#ifndef _actor_serializer_
#define _actor_serializer_

#include <string>
#include "actor.h"

namespace rapinae {
std::string serialize_to_json(const rapinae::RWActor &actor, const bool only_updated_attrs);
}

#endif