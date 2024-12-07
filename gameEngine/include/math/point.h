#ifndef POINT_H
#define POINT_H

struct Point {
  float x, y;

  Point projectPointOntoLine(Point a, Point b);
  float length();
  Point normalized();
  Point inverted();

  Point operator+(const Point& point) const;
  Point operator/(float number) const;
  Point operator-(const Point& point) const;
  Point operator*(float number) const;
  bool operator==(const Point& point) const;
  bool isOnSegment(Point segmentStart, Point segmentEnd);
};

#endif // POINT_H
