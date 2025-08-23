#pragma once
#include "vector.hpp"

struct Mat4
{
  float elements[4][4];
  Mat4() : elements{{0}}
  {
  }
};

Mat4 mat4_identity(void);
Mat4 mat4_make_scale(float sx, float sy, float sz);
Mat4 mat4_make_translation(float tx, float ty, float tz);
Vec4 mat4_mul_vec4(Mat4 m, Vec4 v);
Mat4 mat4_make_rotation_x(float angle);
Mat4 mat4_make_rotation_y(float angle);
Mat4 mat4_make_rotation_z(float angle);
