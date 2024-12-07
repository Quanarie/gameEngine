#include <complex>

#include "math/point.h"

Point Point::projectPointOntoLine(Point a, Point b) {
  Point AB = b - a;

  Point AP = *this - a;

  float dotProduct = AP.x * AB.x + AP.y * AB.y;
  float abMagnitudeSquared = AB.x * AB.x + AB.y * AB.y;

  Point projectedPoint = a + AB * (dotProduct / abMagnitudeSquared);

  return projectedPoint;
}

Point Point::normalized() {
  return *this / this->length();
}

float Point::length() {
  return std::sqrt(this->x * this->x + this->y * this->y);
}

Point Point::operator+(const Point& point) const {
  return Point(this->x + point.x, this->y + point.y);
}

Point Point::operator/(int number) const {
  return Point{this->x / number, this->y / number};
}

Point Point::operator-(const Point& point) const {
  return Point(this->x - point.x, this->y - point.y);
}

Point Point::operator*(float number) const {
  return Point(this->x * number, this->y * number);
}

bool Point::operator==(const Point& point) const {
  return this->x == point.x && this->y == point.y;
}

bool Point::isOnSegment(Point segmentStart, Point segmentEnd) {
  return (segmentStart - *this).length() + (segmentEnd - *this).length() == (segmentStart - segmentEnd).length();
}
