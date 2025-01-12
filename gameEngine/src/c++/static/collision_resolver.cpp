#include <array>
#include <vector>

#include "static/geometry.h"
#include "static/collision_resolver.h"
#include "static/coordinates_converter.h"
#include "component/transform_component.h"
#include "component/collider/rectangle/rectangle_corners.h"
#include "component/collider/ellipse/ellipse_colider_component.h"
#include "component/collider/rectangle/rectangle_colider_component.h"

#define ELLIPSE_APPROX_VERTICES_AMOUNT 100

void doResolve(const ColliderComponent& coll1,
               const ColliderComponent& coll2,
               Vector resolutionVector)
{
  if (!coll1.isStatic && !coll2.isStatic)
  {
    coll1.transform->pos = coll1.transform->pos + resolutionVector / 2;
    coll2.transform->pos = coll2.transform->pos - resolutionVector / 2;
  }
  else if (!coll1.isStatic || !coll2.isStatic)
  {
    coll1.transform->pos = coll1.transform->pos + resolutionVector * (coll1.isStatic && !coll2.isStatic ? 0 : 1);
    coll2.transform->pos = coll2.transform->pos - resolutionVector * (coll2.isStatic && !coll1.isStatic ? 0 : 1);
  }
}

std::vector<Vector> getRectCornersAsVector(RectangleCorners& rect)
{
  return std::vector{rect[0], rect[1], rect[2], rect[3]};
}

bool CollisionResolver::resolve(const RectangleColliderComponent& rect1, const RectangleColliderComponent& rect2)
{
  auto rect1Corners = rect1.getTransformedCorners();
  auto rect2Corners = rect2.getTransformedCorners();

  std::vector<Vector> rect1Vertices = getRectCornersAsVector(rect1Corners);
  std::vector<Vector> rect2Vertices = getRectCornersAsVector(rect2Corners);

  Vector collisionNormal;
  float penetrationDepth = Geometry::calculatePenetration(
    rect1Vertices,
    (rect1Corners.ld + rect1Corners.ru) / 2,
    rect2Vertices,
    (rect2Corners.ld + rect2Corners.ru) / 2,
    collisionNormal
  );

  if (penetrationDepth == 0.0f)
    return false;

  Vector resolutionVector = collisionNormal * penetrationDepth;
  doResolve(rect1, rect2, resolutionVector);

  return true;
}

// TODO: takes a lot time to check afterwards. Do it without approx. And move to Geometry
std::vector<Vector> getEllipApproxAsPolygon(Vector ellipCenter, Vector scaledAxes, int numVertices,
                                            TransformComponent& trans)
{
  std::vector<Vector> vertices;
  vertices.reserve(numVertices);

  float angleIncrement = 2.0f * M_PI / numVertices;
  float rotation = -trans.getRotationRad(); // minus because of SDL rendering

  for (int i = 0; i < numVertices; ++i)
  {
    float angle = i * angleIncrement;

    float x = scaledAxes.x * std::cos(angle);
    float y = scaledAxes.y * std::sin(angle);

    float xRotated = x * cos(rotation) - y * sin(rotation) + ellipCenter.x;
    float yRotated = x * sin(rotation) + y * cos(rotation) + ellipCenter.y;

    vertices.emplace_back(Vector(xRotated, yRotated));
  }

  return vertices;
}

bool CollisionResolver::resolve(const EllipseColliderComponent& ellip, const RectangleColliderComponent& rect)
{
  auto rectCorners = rect.getTransformedCorners();
  Vector ellipCenter = ellip.getTransformedCenter();

  std::vector<Vector> rect1Vertices = getRectCornersAsVector(rectCorners);
  std::vector<Vector> ellipVertices = getEllipApproxAsPolygon(ellipCenter, ellip.getScaledAxes(),
                                                              ELLIPSE_APPROX_VERTICES_AMOUNT, *ellip.transform);

  Vector collisionNormal;
  float penetrationDepth = Geometry::calculatePenetration(
    rect1Vertices,
    (rectCorners.ld + rectCorners.ru) / 2,
    ellipVertices,
    ellipCenter,
    collisionNormal
  );

  if (penetrationDepth == 0.0f)
    return false;

  Vector resolutionVector = collisionNormal * penetrationDepth;
  doResolve(rect, ellip, resolutionVector);

  return true;
}

bool CollisionResolver::resolve(const EllipseColliderComponent& ell1,
                                const EllipseColliderComponent& ell2)
{
  Vector ell1Center = ell1.getTransformedCenter();
  Vector ell2Center = ell2.getTransformedCenter();

  std::vector<Vector> ell1Vertices = getEllipApproxAsPolygon(ell1Center, ell1.getScaledAxes(),
                                                             ELLIPSE_APPROX_VERTICES_AMOUNT, *ell1.transform);
  std::vector<Vector> ell2Vertices = getEllipApproxAsPolygon(ell2Center, ell2.getScaledAxes(),
                                                             ELLIPSE_APPROX_VERTICES_AMOUNT, *ell2.transform);

  Vector collisionNormal;
  float penetrationDepth = Geometry::calculatePenetration(
    ell1Vertices,
    ell1Center,
    ell2Vertices,
    ell2Center,
    collisionNormal
  );

  if (penetrationDepth == 0.0f)
    return false;

  Vector resolutionVector = collisionNormal * penetrationDepth;
  doResolve(ell1, ell2, resolutionVector);

  return true;
}
