#include "static/coordinates_converter.h"

Vector CoordinatesConverter::resolution = {0.0f, 0.0f};

void CoordinatesConverter::setResolution(int resX, int resY) {
  resolution = Vector{static_cast<float>(resX), static_cast<float>(resY)};
}

Vector CoordinatesConverter::toMyCoordinates(Vector v) {
  return (v * Vector{1.0f, -1.0f} - resolution/2);
}

Vector CoordinatesConverter::toSdlCoordinates(Vector v) {
  return (v * Vector{1.0f, -1.0f} + resolution/2);
}
