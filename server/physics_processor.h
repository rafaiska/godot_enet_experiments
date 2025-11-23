#ifndef _physics_processor_
#define _physics_processor_

#include "actor.h"
#include "vector.h"
#include <vector>
namespace rapinae {
class PhysicsProcessor {
    public:
        PhysicsProcessor(const Vector2 &size);
        void update_velocity(std::vector<RWActor> &actors, const float &delta);
    private:
        float width;
        float height;
        Vector2 upper_left = Vector2(0.0, 0.0);
        Vector2 lower_right = Vector2(0.0, 0.0);
};
} // namespace rapinae

#endif