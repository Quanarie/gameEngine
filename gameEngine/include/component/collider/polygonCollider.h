#ifndef POLYGON_COLLIDER_H
#define POLYGON_COLLIDER_H

#include <SDL.h>
#include <SDL_rect.h>
#include <vector>

#include "component/component.h"
#include "component/transform.h"
#include "math/point.h"

struct CollisionResult {
  bool collided;
  float overlap;
  Point direction;
};

class PolygonColliderComponent : public Component {
public:
  PolygonColliderComponent(std::initializer_list<Point> points,
                           TransformComponent *transform)
      : localPoints(points), transform(transform) {
    updateGlobalPoints();
  }

  CollisionResult isColliding(PolygonColliderComponent *otherCollider);
  void updateGlobalPoints();
  const std::vector<Point> &getGlobalPoints() const { return globalPoints; }

private:
  TransformComponent *transform;
  std::vector<Point> localPoints;
  std::vector<Point> globalPoints;
  std::vector<Point> getAxes();
  void projectOntoAxis(Point &axis, float &min, float &max);
};

#endif // POLYGON_COLLIDER_H
