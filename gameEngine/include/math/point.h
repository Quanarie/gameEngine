#ifndef POINT_H
#define POINT_H

struct Point {
  float x, y;

  Point operator+(const Point& point) const;
};

#endif // POINT_H
