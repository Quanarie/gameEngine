#include <catch2/catch_test_macros.hpp>

#include "util/vector.h"
#include "component/transform_component.h"
#include "component/collider/collision_resolver.h"
#include "component/collider/ellipse/ellipse_colider_component.h"
#include "component/collider/rectangle/rectangle_colider_component.h"

// TODO: think about intersections when its just touching and also that collisionResolver kinda
// doesnt resolve it, it still returs true and touches
TEST_CASE("Rectangles intersect") {
  auto rect1 = new RectangleColliderComponent(Vector{0.0f, 0.0f}, Vector{30.0f, 30.0f});
  auto trans1 = new TransformComponent(Vector{0.0f, 0.0f});
  auto rect2 = new RectangleColliderComponent(Vector{0.0f, 30.0f}, Vector{40.0f, 40.0f});
  auto trans2 = new TransformComponent(Vector{20.0f, 0.0f});

  REQUIRE(CollisionResolver::resolve(*rect1, *trans1, *rect2, *trans2) == true);
  delete rect1;
  delete trans1;
  delete rect2;
  delete trans2;
}

TEST_CASE("Rectangles touch") {
  auto rect1 = new RectangleColliderComponent(Vector{0.0f, 0.0f}, Vector{30.0f, 30.0f});
  auto trans1 = new TransformComponent(Vector{0.0f, 0.0f});
  auto rect2 = new RectangleColliderComponent(Vector{30.0f, 30.0f}, Vector{40.0f, 40.0f});
  auto trans2 = new TransformComponent(Vector{0.0f, 0.0f});

  REQUIRE(CollisionResolver::resolve(*rect1, *trans1, *rect2, *trans2) == true);
  delete rect1;
  delete trans1;
  delete rect2;
  delete trans2;
}

TEST_CASE("Rectangle and ellipse intersect") {
  auto ell = new EllipseColliderComponent(Vector{0.0f, 0.0f}, EllipseAxes{5.0f, 10.0f});
  auto transEll = new TransformComponent(Vector{1.0f, 1.0f});
  auto rect = new RectangleColliderComponent(Vector{4.0f, 5.0f}, Vector{10.0f, 10.0f});
  auto transRect = new TransformComponent(Vector{1.0f, 0.0f});

  REQUIRE(CollisionResolver::resolve(*ell, *transEll, *rect, *transRect) == true);
  delete ell;
  delete transEll;
  delete rect;
  delete transRect;
}

TEST_CASE("Ellipses intersect") {
  auto ell1 = new EllipseColliderComponent(Vector{1.0f, 1.0f}, EllipseAxes{5.0f, 10.0f});
  auto trans1 = new TransformComponent(Vector{0.0f, 0.0f});
  auto ell2 = new EllipseColliderComponent(Vector{8.0f, 10.0f}, EllipseAxes{4.0f, 12.0f});
  auto trans2 = new TransformComponent(Vector{0.0f, 0.0f});

  REQUIRE(CollisionResolver::resolve(*ell1, *trans1, *ell2, *trans2) == true);
  delete ell1;
  delete trans1;
  delete ell2;
  delete trans2;
}