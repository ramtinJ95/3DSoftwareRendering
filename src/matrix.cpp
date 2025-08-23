#include "matrix.hpp"

Mat4 mat4_identity()
{
  Mat4 matrix;
  matrix.elements[0][0] = 1.0f;
  matrix.elements[1][1] = 1.0f;
  matrix.elements[2][2] = 1.0f;
  matrix.elements[3][3] = 1.0f;
  return matrix;
}

Mat4 mat4_make_scale(float sx, float sy, float sz)
{
  Mat4 matrix;
  matrix.elements[0][0] = sx;
  matrix.elements[1][1] = sy;
  matrix.elements[2][2] = sz;
  matrix.elements[3][3] = 1.0f;
  return matrix;
}

Vec4 mat4_mul_vec4(Mat4 m, Vec4 v)
{
  Vec4 result;
  result.x = v.x * m.elements[0][0] + v.y * m.elements[1][0] + v.z * m.elements[2][0] +
             v.w * m.elements[3][0];
  result.y = v.x * m.elements[0][1] + v.y * m.elements[1][1] + v.z * m.elements[2][1] +
             v.w * m.elements[3][1];
  result.z = v.x * m.elements[0][2] + v.y * m.elements[1][2] + v.z * m.elements[2][2] +
             v.w * m.elements[3][2];
  result.w = v.x * m.elements[0][3] + v.y * m.elements[1][3] + v.z * m.elements[2][3] +
             v.w * m.elements[3][3];
  return result;
}
