#ifndef COLLISION_RESOLVER_H
#define COLLISION_RESOLVER_H

class TransformComponent;
class RectangleColliderComponent;
class EllipseColliderComponent;

class CollisionResolver
{
public:
  static bool resolve(const RectangleColliderComponent& rect1, const RectangleColliderComponent& rect2);
  static bool resolve(const EllipseColliderComponent& ellip, const RectangleColliderComponent& rect);
  static bool resolve(const EllipseColliderComponent& ell1, const EllipseColliderComponent& ell2);
};

#endif // COLLISION_RESOLVER_H
