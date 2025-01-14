#include <complex>

#include "util/vector.h"

#define IS_ON_SEGMENT_EPSILON 0.05f

Vector Vector::projectOntoLine(Vector a, Vector b)
{
  Vector AB = b - a;

  Vector AP = *this - a;

  float dotProduct = AP.x * AB.x + AP.y * AB.y;
  float abMagnitudeSquared = AB.x * AB.x + AB.y * AB.y;

  Vector projectedPoint = a + AB * (dotProduct / abMagnitudeSquared);

  return projectedPoint;
}

Vector Vector::normalized() { return *this / this->length(); }

Vector Vector::inverted() { return Vector{this->y, this->x}; }

float Vector::length() { return std::sqrt(this->x * this->x + this->y * this->y); }

Vector Vector::operator+(const Vector& point) const { return Vector(this->x + point.x, this->y + point.y); }

Vector Vector::operator/(float number) const { return Vector{this->x / number, this->y / number}; }

Vector Vector::operator-(const Vector& point) const { return Vector(this->x - point.x, this->y - point.y); }

Vector Vector::operator*(float number) const { return Vector(this->x * number, this->y * number); }

Vector Vector::operator*(const Vector& point) const { return Vector{this->x * point.x, this->y * point.y}; }

bool Vector::operator==(const Vector& point) const { return this->x == point.x && this->y == point.y; }

bool Vector::isOnSegment(Vector segmentStart, Vector segmentEnd)
{
  return std::abs(
      (segmentStart - *this).length() + (segmentEnd - *this).length() - (segmentStart - segmentEnd).length()) <
    IS_ON_SEGMENT_EPSILON;
}

float Vector::dot(Vector v)
{
  return this->x * v.x + this->y * v.y;
}

Vector Vector::rotateAroundPointRad(Vector p, float rot)
{
  return Vector{
    p.x + (this->x - p.x) * cos(rot) - (this->y - p.y) * sin(rot),
    p.y + (this->x - p.x) * sin(rot) + (this->y - p.y) * cos(rot)
  };
}
