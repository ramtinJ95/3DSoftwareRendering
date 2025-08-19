#pragma once
#include "vector.hpp"

struct Face
{
  int a, b, c;

  // Default constructor
  Face() : a(0), b(0), c(0)
  {
  }

  // Constructor with parameters
  Face(int a_, int b_, int c_) : a(a_), b(b_), c(c_)
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

void draw_filled_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);
void draw_flat_top_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);
void draw_flat_bottom_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);
