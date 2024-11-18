#include <SDL.h>
#include <SDL_timer.h>

#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <vector>

#include "component/collider/polygonCollider.h"
#include "math/utils.h"

CollisionResult
PolygonColliderComponent::isColliding(PolygonColliderComponent *otherCollider) {
  CollisionResult result = {false, 0.0f, {0.0f, 0.0f}};

  float minOverlap = std::numeric_limits<float>::max();
  Point smallestAxis = {0.0f, 0.0f};

  std::vector<Point> axes = getAxes();
  std::vector<Point> otherAxes = otherCollider->getAxes();
  axes.insert(axes.end(), otherAxes.begin(), otherAxes.end());

  for (auto &axis : axes) {
    float minA, maxA, minB, maxB;

    projectOntoAxis(axis, minA, maxA);
    otherCollider->projectOntoAxis(axis, minB, maxB);

    if (maxA < minB || maxB < minA) {
      return result;
    }

    float overlap = std::min(maxA, maxB) - std::max(minA, minB);
    if (overlap < minOverlap) {
      minOverlap = overlap;
      smallestAxis = axis;
    }
  }

  float length = std::sqrt(smallestAxis.x * smallestAxis.x +
                           smallestAxis.y * smallestAxis.y);
  smallestAxis.x /= length;
  smallestAxis.y /= length;

  result.collided = true;
  result.overlap = minOverlap;
  result.direction = smallestAxis;
  return result;
}

void PolygonColliderComponent::updateGlobalPoints() {
  globalPoints.clear();
  for (Point &point : localPoints) {
    globalPoints.push_back(
        {point.x + transform->point.x, point.y + transform->point.y});
  }
}

std::vector<Point> PolygonColliderComponent::getAxes() {
  std::vector<Point> axes;
  for (size_t i = 0; i < globalPoints.size(); ++i) {
    Point p1 = globalPoints[i];
    Point p2 = globalPoints[(i + 1) % globalPoints.size()];
    Point edge = {p2.x - p1.x, p2.y - p1.y};
    Point normal = {edge.y, -edge.x};
    Utils::normalize(normal);
    axes.push_back(normal);
  }
  return axes;
}

void PolygonColliderComponent::projectOntoAxis(Point &axis, float &min,
                                               float &max) {
  min = max = globalPoints[0].x * axis.x + globalPoints[0].y * axis.y;
  for (const auto &point : globalPoints) {
    float projection = point.x * axis.x + point.y * axis.y;
    if (projection < min)
      min = projection;
    if (projection > max)
      max = projection;
  }
}
