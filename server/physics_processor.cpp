#include "physics_processor.h"
#include "actor.h"
#include "vector.h"
#include <enet/protocol.h>

rapinae::PhysicsProcessor::PhysicsProcessor(const Vector2 &size) {
  width = size.x;
  height = size.y;
  upper_left = Vector2(-(size.x / 2.0), -(size.y / 2.0));
  lower_right = Vector2(size.x / 2.0, size.y / 2.0);
}

void rapinae::PhysicsProcessor::update_velocity(std::vector<RWActor> &actors,
                                                const float &delta) {
  for (RWActor &actor : actors) {
    if (actor.has_attr("lin_vel") && actor.has_attr("position")) {
      Vector2 *vel = (Vector2 *)actor.get_void_attr("lin_vel");
      Vector2 *position = (Vector2 *)actor.get_void_attr("position");

      position->x += vel->x * delta / 1000.0;
      if (position->x < upper_left.x)
        position->x += width;
      else if (position->x > lower_right.x)
        position->x -= width;

      position->y += vel->y * delta / 1000.0;
      if (position->y < upper_left.y)
        position->y += height;
      else if (position->y > lower_right.y)
        position->y -= height;
      actor.set_attr_updated("position");
    }
  }
}