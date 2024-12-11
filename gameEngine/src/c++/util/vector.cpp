#include <complex>

#include "util/vector.h"

Vector Vector::projectPointOntoLine(Vector a, Vector b) {
  Vector AB = b - a;

  Vector AP = *this - a;

  float dotProduct = AP.x * AB.x + AP.y * AB.y;
  float abMagnitudeSquared = AB.x * AB.x + AB.y * AB.y;

  Vector projectedPoint = a + AB * (dotProduct / abMagnitudeSquared);

  return projectedPoint;
}

Vector Vector::normalized() {
  return *this / this->length();
}

Vector Vector::inverted() {
  return Vector{this->y, this->x};
}

float Vector::length() {
  return std::sqrt(this->x * this->x + this->y * this->y);
}

Vector Vector::operator+(const Vector& point) const {
  return Vector(this->x + point.x, this->y + point.y);
}

Vector Vector::operator/(float number) const {
  return Vector{this->x / number, this->y / number};
}

Vector Vector::operator-(const Vector& point) const {
  return Vector(this->x - point.x, this->y - point.y);
}

Vector Vector::operator*(float number) const {
  return Vector(this->x * number, this->y * number);
}

bool Vector::operator==(const Vector& point) const {
  return this->x == point.x && this->y == point.y;
}

bool Vector::isOnSegment(Vector segmentStart, Vector segmentEnd) {
  return (segmentStart - *this).length() + (segmentEnd - *this).length() == (segmentStart - segmentEnd).length();
}
