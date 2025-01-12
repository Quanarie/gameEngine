#include "static/collision_resolver.h"
#include "component/transform_component.h"
#include "component/collider/rectangle/rectangle_corners.h"
#include "component/collider/rectangle/rectangle_colider_component.h"

bool RectangleColliderComponent::resolve(const ColliderComponent& other) const
{
  return other.resolveWith(*this);
}

bool RectangleColliderComponent::resolveWith(const RectangleColliderComponent& rect) const
{
  return CollisionResolver::resolve(rect, *this);
}

bool RectangleColliderComponent::resolveWith(const EllipseColliderComponent& ellipse) const
{
  return CollisionResolver::resolve(ellipse, *this);
}

RectangleCorners RectangleColliderComponent::getTransformedCorners() const
{
  Vector LD = leftDown, RU = rightUp;
  Vector LU = {LD.x, RU.y}, RD = {RU.x, LD.y};

  Vector rp = (LD + RU) / 2;
  float rot = this->transform->getRotationRad();
  Vector LURot = LU.rotateAroundPointRad(rp, rot);
  Vector RURot = RU.rotateAroundPointRad(rp, rot);
  Vector LDRot = LD.rotateAroundPointRad(rp, rot);
  Vector RDRot = RD.rotateAroundPointRad(rp, rot);

  TransformComponent* myTr = this->transform;
  LD = LDRot * myTr->scale + myTr->pos;
  RU = RURot * myTr->scale + myTr->pos;
  LU = LURot * myTr->scale + myTr->pos;
  RD = RDRot * myTr->scale + myTr->pos;

  return RectangleCorners{LD, LU, RU, RD};
}
