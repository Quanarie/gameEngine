#include "component/collider/collision_detector.h"

#include <array>
#include <vector>
#include <__algorithm/clamp.h>

#include "inputs.h"
#include "component/transform_component.h"
#include "component/collider/ellipse_colider_component.h"
#include "component/collider/rectangle_colider_component.h"
#include "math/point.h"

struct OverlapResult {
  bool doesOverlap;
  Point shortestOverlapResolutionVector;
  float overlapValue;
};

OverlapResult doesPointOverlapRect(std::array<Point, 4> rect1Corners, int cornerIndex,
                                   std::array<Point, 4> rect2Corners) {
  Point corner = rect1Corners[cornerIndex];

  float minDistance = std::numeric_limits<float>::max();
  Point shortestResolutionVector = {0, 0};

  OverlapResult notOverlapping = {
    false,
    Point{std::numeric_limits<float>::max(), std::numeric_limits<float>::max()},
    std::numeric_limits<float>::max()
  };

  for (int i = 0; i < rect2Corners.size(); i++) {
    Point segmentStart = rect2Corners[i];
    Point segmentEnd = rect2Corners[(i + 1) % 4];

    Point projectedPoint = corner.projectPointOntoLine(segmentStart, segmentEnd);
    if (!projectedPoint.isInsideSegment(segmentStart, segmentEnd))
      return notOverlapping;

    Point resolutionVector = projectedPoint - corner;
    float distance = resolutionVector.length();

    std::array<Point, 4> rect1CornersResolved = {};
    std::array<Point, 4> rect2CornersResolved = {};
    for (int j = 0; j < rect1Corners.size(); j++) {
      rect1CornersResolved[j] = rect1Corners[j] + resolutionVector / 2;
      rect2CornersResolved[j] = rect2Corners[j] - resolutionVector / 2;
    }
    if (я ебу нахуй сук за шо) {
      if (distance < minDistance) {
        minDistance = distance;
        shortestResolutionVector = resolutionVector;
      }
    }
  }

  return {true, shortestResolutionVector, minDistance};
}

bool checkAnyCornerOfRect1InsideRect2AndResolve(const RectangleColliderComponent& rect1,
                                                TransformComponent& trans1,
                                                const RectangleColliderComponent& rect2,
                                                TransformComponent& trans2) {
  auto rect1Corners = rect1.getTransformedCorners(trans1.position);
  auto rect2Corners = rect2.getTransformedCorners(trans2.position);

  OverlapResult minOverlapResult = doesPointOverlapRect(rect1Corners, 0, rect2Corners);
  for (int i = 1; i < rect1Corners.size(); i++) {
    OverlapResult overlapResult = doesPointOverlapRect(rect1Corners, i, rect2Corners);
    if (overlapResult.doesOverlap && overlapResult.overlapValue < minOverlapResult.overlapValue) {
      minOverlapResult = overlapResult;
    }
  }

  if (!minOverlapResult.doesOverlap)
    return false;

  trans1.position = trans1.position + minOverlapResult.shortestOverlapResolutionVector / 2;
  trans2.position = trans2.position - minOverlapResult.shortestOverlapResolutionVector / 2;

  return true;
}

// Create tests for this pls
bool CollisionResolver::resolve(const RectangleColliderComponent& rect1,
                                TransformComponent& trans1,
                                const RectangleColliderComponent& rect2,
                                TransformComponent& trans2) {
  if (Inputs::isKeyHeld(SDL_SCANCODE_S)) {
    int a;
  }
  // We need to check if any corner of rect1 is in rect2 or vice versa, cuz rectangles can be rotated (in future)
  if (checkAnyCornerOfRect1InsideRect2AndResolve(rect1, trans1, rect2, trans2))
    return true;

  if (checkAnyCornerOfRect1InsideRect2AndResolve(rect2, trans2, rect1, trans1))
    return true;

  return false;
}


bool CollisionResolver::resolve(const EllipseColliderComponent& ellip,
                                TransformComponent& transEllip,
                                const RectangleColliderComponent& rect,
                                TransformComponent& transRect) {
  Point ellipCenter = ellip.getTransformedCenter(transEllip.position);
  auto [rect1LD, rect1RU] = rect.getTransformedDefiningCorners(transRect.position);

  auto closestPointToEllipInRect = Point{
    std::clamp(ellipCenter.x, rect1LD.x, rect1RU.x),
    std::clamp(ellipCenter.y, rect1LD.y, rect1RU.y)
  };

  auto relativeToEllip = Point{
    ellipCenter.x - closestPointToEllipInRect.x,
    ellipCenter.y - closestPointToEllipInRect.y
  };

  return (relativeToEllip.x * relativeToEllip.x) / (ellip.radiuses.x * ellip.radiuses.x) +
    (relativeToEllip.y * relativeToEllip.y) / (ellip.radiuses.y * ellip.radiuses.y) <= 1;
}

bool CollisionResolver::resolve(const EllipseColliderComponent& ell1,
                                TransformComponent& trans1,
                                const EllipseColliderComponent& ell2,
                                TransformComponent& trans2) {
  Point ell1Center = ell1.center + trans1.position;
  Point ell2Center = ell2.center + trans2.position;

  // Treating 2 center as a point we should check to lie within a "combined" ellipse
  // Intuitively: we can shrink second ellipse and expand first as much till second becomes just a point
  // Curvature of ellipses are same so shrinking and expanding is equivalent
  Point center2RelatTo1 = Point{
    ell2Center.x - ell1Center.x,
    ell2Center.y - ell1Center.y
  };

  Point combinedRads = Point{
    ell1.radiuses.x + ell2.radiuses.x,
    ell1.radiuses.y + ell2.radiuses.y
  };

  return center2RelatTo1.x * center2RelatTo1.x / (combinedRads.x * combinedRads.x) +
    center2RelatTo1.y * center2RelatTo1.y / (combinedRads.y * combinedRads.y) <= 1;
}
