#ifndef RECTANGLE_COLLIDER_COMPONENT_H
#define RECTANGLE_COLLIDER_COMPONENT_H

#include "collider_component.h"

class RectangleColliderComponent : public ColliderComponent {
public:
  RectangleColliderComponent(Point ld, Point ru)
    : leftDown(ld), rightUp(ru) {}

  // For now public
  Point leftDown, rightUp;
};

#endif // RECTANGLE_COLLIDER_COMPONENT_H
