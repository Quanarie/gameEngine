#include <catch2/catch_test_macros.hpp>

#include "util/vector.h"
#include "component/transform_component.h"
#include "component/collider/collision_resolver.h"
#include "component/collider/ellipse/ellipse_colider_component.h"
#include "component/collider/rectangle/rectangle_colider_component.h"

TEST_CASE("Rectangles intersect") {
  auto rect1 = new RectangleColliderComponent(Vector{0.0f, 0.0f}, Vector{30.0f, -30.0f});
  auto trans1 = new TransformComponent(Vector{5.0f, -5.0f});
  auto rect2 = new RectangleColliderComponent(Vector{10.0f, -10.0f}, Vector{40.0f, -40.0f});
  auto trans2 = new TransformComponent(Vector{5.0f, -5.0f});

  REQUIRE(CollisionResolver::resolve(*rect1, *trans1, *rect2, *trans2) == true);
  delete rect1;
  delete trans1;
  delete rect2;
  delete trans2;
}

TEST_CASE("Rectangle and ellipse intersect") {
  auto ell = new EllipseColliderComponent(Vector{0.0f, 0.0f}, EllipseAxes{10.0f, 10.0f});
  auto transEll = new TransformComponent(Vector{5.0f, -5.0f});
  auto rect = new RectangleColliderComponent(Vector{0.0f, 0.0f}, Vector{30.0f, -30.0f});
  auto transRect = new TransformComponent(Vector{5.0f, -5.0f});

  REQUIRE(CollisionResolver::resolve(*ell, *transEll, *rect, *transRect) == true);
  delete ell;
  delete transEll;
  delete rect;
  delete transRect;
}
