#ifndef POINT_H
#define POINT_H

struct Vector {
  float x, y;

  float length();
  Vector normalized();
  Vector inverted();
  Vector projectOntoLine(Vector a, Vector b);

  // TODO: add += and change + occurrences
  Vector operator+(const Vector& point) const;
  Vector operator-(const Vector& point) const;
  Vector operator*(const Vector& point) const;
  bool operator==(const Vector& point) const;

  Vector operator/(float number) const;
  Vector operator*(float number) const;

  bool isOnSegment(Vector segmentStart, Vector segmentEnd);
  float dot(Vector v);
  Vector rotateAroundPointRad(Vector p, float rot);
};

#endif // POINT_H
