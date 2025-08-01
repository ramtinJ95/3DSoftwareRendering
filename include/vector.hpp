#pragma once
#include <math.h>

struct Vec2
{
  float x, y;
  Vec2() : x(0.0f), y(0.0f)
  {
  }
  Vec2(float x_, float y_) : x(x_), y(y_)
  {
  }
};

struct Vec3
{
  float x, y, z;
  Vec3() : x(0.0f), y(0.0f), z(0.0f)
  {
  }
  Vec3(float x_, float y_, float z_) : x(x_), y(y_), z(z_)
  {
  }
};

inline Vec3 vec3_rotate_x(const Vec3 *v, float angle)
{
  Vec3 rotated_vector(v->x, v->y * cos(angle) - v->z * sin(angle),
                      v->y * sin(angle) + v->z * cos(angle));
  return rotated_vector;
}

inline Vec3 vec3_rotate_y(const Vec3 *v, float angle)
{
  Vec3 rotated_vector(v->x * cos(angle) - v->z * sin(angle), v->y,
                      v->x * sin(angle) + v->z * cos(angle));
  return rotated_vector;
}

inline Vec3 vec3_rotate_z(const Vec3 *v, float angle)
{
  Vec3 rotated_vector(v->x * cos(angle) - v->y * sin(angle), v->x * sin(angle) + v->y * cos(angle),
                      v->z);
  return rotated_vector;
}
