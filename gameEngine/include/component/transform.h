#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "component/component.h"
#include "math/point.h"

class TransformComponent : public Component {
public:
  TransformComponent(Point p, float rot = 0.0f, float sX = 1.0f,
                     float sY = 1.0f)
      : point(p), rotation(rot), scaleX(sX), scaleY(sY) {}

  Point point;
  float rotation;
  float scaleX, scaleY;
};

#endif // TRANSFORM_H
