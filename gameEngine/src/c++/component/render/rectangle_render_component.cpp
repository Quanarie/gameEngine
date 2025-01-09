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

  Vector rp = (LD + RU)/2;
  float rot = this->transform->getRotationRad();
  Vector LURot = LU.rotateAroundPointRad(rp, rot);
  Vector RURot = RU.rotateAroundPointRad(rp, rot);
  Vector LDRot = LD.rotateAroundPointRad(rp, rot);
  Vector RDRot = RD.rotateAroundPointRad(rp, rot);

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
