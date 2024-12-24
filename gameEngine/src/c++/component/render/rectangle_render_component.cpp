#include <algorithm>
#include <SDL_render.h>
#include <static/geometry.h>

#include "static/coordinates_converter.h"
#include "component/transform_component.h"
#include "component/render/rectangle_render_component.h"

void RectangleRenderComponent::render(SDL_Renderer* renderer)
{
  // TODO: Take out similar logic from renderers and colliders:
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

  Vector convertedCoords = CoordinatesConverter::toSdlCoordinates(transform->pos);
  LD = LDRot * Vector{1.0f, -1.0f} * transform->scale + convertedCoords;
  RU = RURot * Vector{1.0f, -1.0f} * transform->scale + convertedCoords;
  LU = LURot * Vector{1.0f, -1.0f} * transform->scale + convertedCoords;
  RD = RDRot * Vector{1.0f, -1.0f} * transform->scale + convertedCoords;

  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderDrawLine(renderer, LD.x, LD.y, LU.x, LU.y);
  SDL_RenderDrawLine(renderer, LU.x, LU.y, RU.x, RU.y);
  SDL_RenderDrawLine(renderer, RU.x, RU.y, RD.x, RD.y);
  SDL_RenderDrawLine(renderer, RD.x, RD.y, LD.x, LD.y);
}
