#include "component/collider/collision_detector.h"

#include <__algorithm/clamp.h>

#include "component/transform_component.h"
#include "component/collider/ellipse_colider_component.h"
#include "component/collider/rectangle_colider_component.h"
#include "math/point.h"

bool CollisionDetector::detect(const RectangleColliderComponent& rect1,
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

bool CollisionDetector::detect(const EllipseColliderComponent& ellipse,
                               const TransformComponent& transformEllipse,
                               const RectangleColliderComponent& rectangle,
                               const TransformComponent& transformRectangle) {
  float ellipseCenterX = ellipse.center.x + transformEllipse.point.x;
  float ellipseCenterY = ellipse.center.y + transformEllipse.point.y;

  float rectLeft = rectangle.leftDown.x + transformRectangle.point.x;
  float rectBottom = rectangle.leftDown.y + transformRectangle.point.y;
  float rectRight = rectangle.rightUp.x + transformRectangle.point.x;
  float rectTop = rectangle.rightUp.y + transformRectangle.point.y;

  float closestX = std::clamp(ellipseCenterX, rectLeft, rectRight);
  float closestY = std::clamp(ellipseCenterY, rectBottom, rectTop);

  float dx = ellipseCenterX - closestX;
  float dy = ellipseCenterY - closestY;

  return (dx * dx) / (ellipse.radiuses.x * ellipse.radiuses.x) +
    (dy * dy) / (ellipse.radiuses.y * ellipse.radiuses.y) <= 1;
}

bool CollisionDetector::detect(const EllipseColliderComponent& ellipse1,
                               const TransformComponent& transform1,
                               const EllipseColliderComponent& ellipse2,
                               const TransformComponent& transform2) {
  float ellipse1CenterX = ellipse1.center.x + transform1.point.x;
  float ellipse1CenterY = ellipse1.center.y + transform1.point.y;

  float ellipse2CenterX = ellipse2.center.x + transform2.point.x;
  float ellipse2CenterY = ellipse2.center.y + transform2.point.y;

  float dx = ellipse1CenterX - ellipse2CenterX;
  float dy = ellipse1CenterY - ellipse2CenterY;

  float rxSum = ellipse1.radiuses.x + ellipse2.radiuses.x;
  float rySum = ellipse1.radiuses.y + ellipse2.radiuses.y;

  return (dx * dx) / (rxSum * rxSum) + (dy * dy) / (rySum * rySum) <= 1;
}
