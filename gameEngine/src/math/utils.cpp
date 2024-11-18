#include <cmath>

#include "math/utils.h"

void Utils::normalize(Point &vector) {
  float length = std::sqrt(vector.x * vector.x + vector.y * vector.y);
  if (length > 0.0f) {
    vector.x /= length;
    vector.y /= length;
  }
}
