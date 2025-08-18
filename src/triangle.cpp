#include "triangle.hpp"
#include "display.hpp"

/*
 * Start from the top (x0, y0)
 * Calculate slope1 and slope2. These are the changes in x per change in y. Essentially treating
 * each leg of the triangle as 2 lines with different slopes. So this 'K' value of the line is
 * the inverse of what we did in school for the equvation of the line
 * Loop all scanline from y0 to middle_y:
 * based on the slopes, calculate new x_start and x_end
 * Draw a line from x_start to x_end
 * Based on the slope values, increment x_start and x_end for the next scanline
 */
void draw_flat_bottom_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color)
{
  float inv_slope1 = (float)(x1 - x0) / (y1 - y0);
  float inv_slope2 = (float)(x2 - x0) / (y2 - y0);

  float x_start, x_end = x0;
  for (int y = y0; y <= y2; y++)
  {
    draw_line(x_start, y, x_end, y, color);
    x_start += inv_slope1;
    x_end += inv_slope2;
  }
}
void draw_flat_top_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color)
{
}

void draw_filled_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color)
{
  // Figure out which vertices are top middle and low based on y value
  //  remember that y grows downwards on screen space
  if (y0 > y1)
  {
    std::swap(y0, y1);
    std::swap(x0, x1);
  }
  if (y1 > y2)
  {
    std::swap(y1, y2);
    std::swap(x1, x2);
  }
  if (y0 > y1)
  {
    std::swap(y0, y1);
    std::swap(x0, x1);
  }
  /*
   * We know that the vector from p0 to p2, lets call it
   * p0p2 can give us the point m for some scaling factor t.
   * Given that we start from p0.
   * p0 + t*p0p2 = m
   *
   * We already know that
   * m.y = p1.y
   *
   * so we only need to solve for the x-component,
   * m.y = p0.y + t * p2p0.y,
   *
   * which gives
   * t = (p1.y - p0.y) / p0p2.y;
   *
   * so, now that we have t, we can plug it in and find
   * m.x = p0.x + t*p0p2.x;
   */
  int middle_y = y1;
  float p0p2_y = y2 - y0;
  float p0p2_x = x2 - x1;
  float t = (y1 - y0) / p0p2_y;
  int middle_x = x0 + t * p0p2_x;

  // TODO: Draw flat bottom triangle
  draw_flat_bottom_triangle(x0, y0, x1, y1, middle_x, middle_y, color);

  // TODO: Draw flat top triangle
}
