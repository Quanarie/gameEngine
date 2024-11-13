#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "component.h"

class TransformComponent : public Component {
public:
  TransformComponent(float posX = 0.0f, float posY = 0.0f, float rot = 0.0f,
                     float sX = 1.0f, float sY = 1.0f)
      : x(posX), y(posY), rotation(rot), scaleX(sX), scaleY(sY) {}

  float x, y;
  float rotation;
  float scaleX, scaleY;
};

#endif // TRANSFORM_H
