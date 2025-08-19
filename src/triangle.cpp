#include "triangle.hpp"
#include "display.hpp"
#include <algorithm>

void draw_flat_bottom_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color)
{
  float slope_1 = (float)(x1 - x0) / (y1 - y0);
  float slope_2 = (float)(x2 - x0) / (y2 - y0);
  float x_start = x0;
  float x_end = x0;
  for (int y = y0; y <= y2; y++)
  {
    draw_line(x_start, y, x_end, y, color);
    x_start += slope_1;
    x_end += slope_2;
  }
}
void draw_flat_top_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color)
{
  float slope_1 = (float)(x2 - x0) / (y2 - y0);
  float slope_2 = (float)(x2 - x1) / (y2 - y1);
  float x_start = x2;
  float x_end = x2;
  for (int y = y2; y >= y0; y--)
  {
    draw_line(x_start, y, x_end, y, color);
    x_start -= slope_1;
    x_end -= slope_2;
  }
}
void draw_filled_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color)
{
  // Sort y vertices by y-component so x0, y0 is the top vertex which means the y value has
  // the to be the smallest because in screen space y grows downwards
  if (y0 > y1)
  {
    std::swap(x0, x1);
    std::swap(y0, y1);
  }
  if (y1 > y2)
  {
    std::swap(x1, x2);
    std::swap(y1, y2);
  }
  if (y0 > y1)
  {
    std::swap(x0, x1);
    std::swap(y0, y1);
  }

  // Find the middle point that divides the triangle into 2, one top and one bottom part
  int middle_y = y1;
  int p0p2_y = y2 - y0;
  int p0p2_x = x2 - x0;
  float t = (float)(y1 - y0) / p0p2_y;
  int middle_x = x0 + t * p0p2_x;
  draw_flat_bottom_triangle(x0, y0, x1, y1, middle_x, middle_y, color);
  draw_flat_top_triangle(x1, y1, middle_x, middle_y, x2, y2, color);
}
