#ifndef COLLIDER_RESOLVER_H
#define COLLIDER_RESOLVER_H

class TransformComponent;
class RectangleColliderComponent;
class EllipseColliderComponent;

class CollisionDetector {
public:
  static bool detect(const RectangleColliderComponent& rect1,
                     const TransformComponent& transform1,
                     const RectangleColliderComponent& rect2,
                     const TransformComponent& transform2);

  static bool detect(const EllipseColliderComponent& ellipse,
                     const TransformComponent& transformEllipse,
                     const RectangleColliderComponent& rectangle,
                     const TransformComponent& transformRectangle);


  static bool detect(const EllipseColliderComponent& ellipse1,
                     const TransformComponent& transform1,
                     const EllipseColliderComponent& ellipse2,
                     const TransformComponent& transform2);
};

#endif // COLLIDER_RESOLVER_H
