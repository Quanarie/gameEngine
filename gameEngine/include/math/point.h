#ifndef POINT_H
#define POINT_H

struct Point {
  float x, y;

  Point operator+(const Point &other) const {
    return {x + other.x, y + other.y};
  }

  Point operator-(const Point &other) const {
    return {x - other.x, y - other.y};
  }

  Point &operator+=(const Point &other) {
    x += other.x;
    y += other.y;
    return *this;
  }

  Point &operator-=(const Point &other) {
    x -= other.x;
    y -= other.y;
    return *this;
  }
};

#endif // POINT_H
