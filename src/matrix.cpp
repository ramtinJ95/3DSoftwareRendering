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
  result.x = m.elements[0][0] * v.x + m.elements[0][1] * v.y + m.elements[0][2] * v.z +
             m.elements[0][3] * v.w;
  result.y = m.elements[1][0] * v.x + m.elements[1][1] * v.y + m.elements[1][2] * v.z +
             m.elements[1][3] * v.w;
  result.z = m.elements[2][0] * v.x + m.elements[2][1] * v.y + m.elements[2][2] * v.z +
             m.elements[2][3] * v.w;
  result.w = m.elements[3][0] * v.x + m.elements[3][1] * v.y + m.elements[3][2] * v.z +
             m.elements[3][3] * v.w;
  return result;
}

Mat4 mat4_make_translation(float tx, float ty, float tz)
{
  Mat4 matrix = mat4_identity();
  matrix.elements[0][3] = tx;
  matrix.elements[1][3] = ty;
  matrix.elements[2][3] = tz;
  return matrix;
}

Mat4 mat4_make_rotation_x(float angle)
{
  Mat4 matrix = mat4_identity();
  float c = cosf(angle);
  float s = sinf(angle);
  matrix.elements[1][1] = c;
  matrix.elements[1][2] = s;
  matrix.elements[2][1] = -s;
  matrix.elements[2][2] = c;
  return matrix;
}

Mat4 mat4_make_rotation_y(float angle)
{
  Mat4 matrix = mat4_identity();
  float c = cosf(angle);
  float s = sinf(angle);
  matrix.elements[0][0] = c;
  matrix.elements[0][2] = -s;
  matrix.elements[2][0] = s;
  matrix.elements[2][2] = c;
  return matrix;
}

Mat4 mat4_make_rotation_z(float angle)
{
  Mat4 matrix = mat4_identity();
  float c = cosf(angle);
  float s = sinf(angle);
  matrix.elements[0][0] = c;
  matrix.elements[0][1] = s;
  matrix.elements[1][0] = -s;
  matrix.elements[1][1] = c;
  return matrix;
}

Mat4 mat4_mul_mat4(const Mat4 &m1, const Mat4 &m2)
{
  Mat4 result;

  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      float sum = 0.0f;
      for (int k = 0; k < 4; k++)
      {
        sum += m1.elements[i][k] * m2.elements[k][j];
      }
      result.elements[i][j] = sum;
    }
  }

  return result;
}
