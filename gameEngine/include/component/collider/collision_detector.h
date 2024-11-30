#ifndef COLLIDER_RESOLVER_H
#define COLLIDER_RESOLVER_H

#include "component/collider/rectangle_colider_component.h"
#include "component/transform_component.h"

class CollisionDetector {
public:
  static bool detect(const RectangleColliderComponent& rect1,
                     const TransformComponent& transform1,
                     const RectangleColliderComponent& rect2,
                     const TransformComponent& transform2) {
    Point rect1LeftDownTransformed = {
      rect1.leftDown.x + transform1.point.x,
      rect1.leftDown.y + transform1.point.y
    };
    Point rect1RightUpTransformed = {
      rect1.rightUp.x + transform1.point.x,
      rect1.rightUp.y + transform1.point.y
    };

    Point rect2LeftDownTransformed = {
      rect2.leftDown.x + transform2.point.x,
      rect2.leftDown.y + transform2.point.y
    };
    Point rect2RightUpTransformed = {
      rect2.rightUp.x + transform2.point.x,
      rect2.rightUp.y + transform2.point.y
    };

    return !(rect1LeftDownTransformed.x > rect2RightUpTransformed.x ||
      rect1RightUpTransformed.x < rect2LeftDownTransformed.x ||
      rect1LeftDownTransformed.y > rect2RightUpTransformed.y ||
      rect1RightUpTransformed.y < rect2LeftDownTransformed.y);
  }

  // static bool detect(const RectangleColliderComponent& rect,
  //                    const EllipseColliderComponent& ellipse) {
  //   float closestX = std::clamp(ellipse.cx, rect.x, rect.x + rect.width);
  //   float closestY = std::clamp(ellipse.cy, rect.y, rect.y + rect.height);
  //
  //   float dx = ellipse.cx - closestX;
  //   float dy = ellipse.cy - closestY;
  //
  //   return (dx * dx) / (ellipse.rx * ellipse.rx) + (dy * dy) / (ellipse.ry *
  //     ellipse.ry) <= 1;
  //   return false;
  // }
  //
  // static bool detect(const EllipseColliderComponent& ellipse1,
  //                    const EllipseColliderComponent& ellipse2) {
  //   float dx = ellipse1.cx - ellipse2.cx;
  //   float dy = ellipse1.cy - ellipse2.cy;
  //   float rxSum = ellipse1.rx + ellipse2.rx;
  //   float rySum = ellipse1.ry + ellipse2.ry;
  //
  //   return (dx * dx) / (rxSum * rxSum) + (dy * dy) / (rySum * rySum) <= 1;
  //   return false;
  // }
};

#endif // COLLIDER_RESOLVER_H
