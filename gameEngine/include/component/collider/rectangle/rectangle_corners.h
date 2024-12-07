#ifndef RECTANGLE_CORNERS_H
#define RECTANGLE_CORNERS_H

#include "math/point.h"

struct RectangleCorners {
  Point ld, lu, ru, rd;

  Point& operator[](std::size_t index) {
    switch (index) {
    case 0: return ld;
    case 1: return lu;
    case 2: return ru;
    case 3: return rd;
    default: throw std::out_of_range("Index out of bounds for RectangleCorners");
    }
  }
};

#endif //RECTANGLE_CORNERS_H
