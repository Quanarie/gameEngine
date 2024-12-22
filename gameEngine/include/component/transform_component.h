#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include "util/vector.h"
#include "component/component.h"

class TransformComponent : public Component {
public:
  TransformComponent(Vector p, float rot = 0.0f, Vector s = {1.0f, 1.0f})
    : pos(p), rot(rot), scale(s) {}

  Vector pos;
  float rot;
  Vector scale;
};

#endif // TRANSFORM_COMPONENT_H
