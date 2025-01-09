#include "static/collision_resolver.h"
#include "component/transform_component.h"
#include "component/collider/rectangle/rectangle_corners.h"
#include "component/collider/rectangle/rectangle_colider_component.h"

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
