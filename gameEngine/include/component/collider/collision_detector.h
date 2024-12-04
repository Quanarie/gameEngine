#ifndef COLLISION_RESOLVER_H
#define COLLISION_RESOLVER_H

class TransformComponent;
class RectangleColliderComponent;
class EllipseColliderComponent;

class CollisionResolver {
public:
  static bool resolve(const RectangleColliderComponent& rect1,
                      TransformComponent& trans1,
                      const RectangleColliderComponent& rect2,
                      TransformComponent& trans2);

  static bool resolve(const EllipseColliderComponent& ellip,
                      TransformComponent& transEllip,
                      const RectangleColliderComponent& rect,
                      TransformComponent& transRect);


  static bool resolve(const EllipseColliderComponent& ell1,
                      TransformComponent& trans1,
                      const EllipseColliderComponent& ell2,
                      TransformComponent& trans2);
};

#endif // COLLISION_RESOLVER_H
