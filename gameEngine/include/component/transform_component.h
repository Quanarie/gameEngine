#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include "component/component.h"
#include "util/vector.h"

class TransformComponent : public Component {
public:
  TransformComponent(Vector p, float rot = 0.0f, Vector s = {1.0f, 1.0f})
    : position(p), rotation(rot), scale(s) {}

  Vector position;
  float rotation;
  Vector scale;
};

#endif // TRANSFORM_COMPONENT_H
