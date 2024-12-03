#ifndef COLLIDER_RESOLVER_H
#define COLLIDER_RESOLVER_H

class TransformComponent;
class RectangleColliderComponent;
class EllipseColliderComponent;

class CollisionDetector {
public:
  static bool detect(const RectangleColliderComponent& rect1,
                     const TransformComponent& trans1,
                     const RectangleColliderComponent& rect2,
                     const TransformComponent& trans2);

  static bool detect(const EllipseColliderComponent& ellip,
                     const TransformComponent& transEllip,
                     const RectangleColliderComponent& rect,
                     const TransformComponent& transRect);


  static bool detect(const EllipseColliderComponent& ell1,
                     const TransformComponent& trans1,
                     const EllipseColliderComponent& ell2,
                     const TransformComponent& trans2);
};

#endif // COLLIDER_RESOLVER_H
