#pragma once
#include "vector.hpp"

struct Face
{
  int v, t, n;

  // Default constructor
  Face() : v(0), t(0), n(0)
  {
  }

  // Constructor with parameters
  Face(int a_, int b_, int c_) : v(a_), t(b_), n(c_)
  {
  }
};

struct Triangle
{
  Vec2 points[3];

  // Default constructor - initializes all points to (0,0)
  Triangle() : points{Vec2(), Vec2(), Vec2()}
  {
  }

  // Constructor with three Vec2 points
  Triangle(const Vec2 &p1, const Vec2 &p2, const Vec2 &p3) : points{p1, p2, p3}
  {
  }

  // Constructor with coordinate values
  Triangle(float x1, float y1, float x2, float y2, float x3, float y3)
      : points{Vec2(x1, y1), Vec2(x2, y2), Vec2(x3, y3)}
  {
  }
};
