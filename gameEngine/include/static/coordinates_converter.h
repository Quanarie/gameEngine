#ifndef COORDINATES_CONVERTER_H
#define COORDINATES_CONVERTER_H

#include "util/vector.h"

class CoordinatesConverter {
public:
  static void setResolution(int resX, int resY);
  static Vector toMyCoordinates(Vector v);
  static Vector toSdlCoordinates(Vector v);
private:
  static Vector resolution;
};

#endif // COORDINATES_CONVERTER_H
