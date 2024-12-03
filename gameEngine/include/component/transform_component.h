#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include "component/component.h"
#include "math/point.h"

class TransformComponent : public Component {
public:
  TransformComponent(Point p, float rot = 0.0f, Point s = {1.0f, 1.0f})
    : position(p), rotation(rot), scale(s) {}

  Point position;
  float rotation;
  Point scale;
};

#endif // TRANSFORM_COMPONENT_H
