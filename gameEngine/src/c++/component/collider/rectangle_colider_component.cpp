#include "static/collision_resolver.h"
#include "component/collider/rectangle/rectangle_corners.h"
#include "component/collider/rectangle/rectangle_colider_component.h"

#include <component/transform_component.h>
#include <static/coordinates_converter.h>

bool RectangleColliderComponent::resolve(const ColliderComponent& other,
                                         TransformComponent& transformThis,
                                         TransformComponent& transformOther) const
{
  return other.resolveWith(*this, transformOther, transformThis);
}

bool RectangleColliderComponent::resolveWith(const RectangleColliderComponent& rect,
                                             TransformComponent& transformThis,
                                             TransformComponent& transformOther) const
{
  return CollisionResolver::resolve(rect, transformOther, *this, transformThis);
}

bool RectangleColliderComponent::resolveWith(const EllipseColliderComponent& ellipse,
                                             TransformComponent& transformThis,
                                             TransformComponent& transformOther) const
{
  return CollisionResolver::resolve(ellipse, transformOther, *this, transformThis);
}

RectangleCorners RectangleColliderComponent::getTransformedCorners() const
{
  Vector LD = leftDown, RU = rightUp;
  Vector LU = {LD.x, RU.y}, RD = {RU.x, LD.y};

  std::optional<Vector> rp = Geometry::findLinesIntersectionPoint(LD, RU, LU, RD);
  if (!rp.has_value())
    throw std::runtime_error(
      "Could not find intersection point of diagonals in rectangle. Something is wrong i guess...");
  Vector rpVal = rp.value();
  float rot = this->transform->getRotationRad();
  Vector LURot = LU.rotateAroundPointRad(rpVal, rot);
  Vector RURot = RU.rotateAroundPointRad(rpVal, rot);
  Vector LDRot = LD.rotateAroundPointRad(rpVal, rot);
  Vector RDRot = RD.rotateAroundPointRad(rpVal, rot);

  TransformComponent* myTr = this->transform;
  LD = LDRot * myTr->scale + myTr->pos;
  RU = RURot * myTr->scale + myTr->pos;
  LU = LURot * myTr->scale + myTr->pos;
  RD = RDRot * myTr->scale + myTr->pos;

  return RectangleCorners{LD, LU, RU, RD};
}
