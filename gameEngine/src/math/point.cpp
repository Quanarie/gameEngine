#include "math/point.h"

Point Point::operator+(const Point& point) const {
  return Point(this->x + point.x, this->y + point.y);
}
