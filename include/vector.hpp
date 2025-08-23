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

struct Vec4
{
  float x, y, z, w;
  Vec4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f)
  {
  }
  Vec4(float x_, float y_, float z_, float w_) : x(x_), y(y_), z(z_), w(w_)
  {
  }
};

inline Vec4 vec3_to_vec4(const Vec3 &v)
{
  Vec4 result(v.x, v.y, v.z, 1.0f);
  return result;
}

inline Vec3 vec4_to_vec3(const Vec4 &v)
{
  Vec3 result(v.x, v.y, v.z);
  return result;
}

inline float vec2_length(const Vec2 &v)
{
  float x_squared = v.x * v.x;
  float y_squared = v.y * v.y;
  float vector_length = sqrtf(x_squared + y_squared);
  return vector_length;
}
inline Vec2 vec2_get_normalized_vector(const Vec2 &v)
{
  Vec2 result_vector = v;
  float length = vec2_length(result_vector);
  result_vector.x /= length;
  result_vector.y /= length;
  return result_vector;
}

inline void vec2_normalize(Vec2 &v)
{
  float length = vec2_length(v);
  v.x /= length;
  v.y /= length;
}

inline Vec2 vec2_add(const Vec2 &v1, const Vec2 &v2)
{
  float x = v1.x + v2.x;
  float y = v1.y + v2.y;
  Vec2 result(x, y);
  return result;
}
inline Vec2 vec2_mul(const Vec2 &v1, const float scalar)
{
  float x = v1.x * scalar;
  float y = v1.y * scalar;
  Vec2 result(x, y);
  return result;
}
inline Vec2 vec2_div(const Vec2 &v1, const float scalar)
{
  float x = v1.x / scalar;
  float y = v1.y / scalar;
  Vec2 result(x, y);
  return result;
}
inline Vec2 vec2_sub(const Vec2 &v1, const Vec2 &v2)
{
  float x = v1.x - v2.x;
  float y = v1.y - v2.y;
  Vec2 result(x, y);
  return result;
}
inline float vec2_dot(const Vec2 &v1, const Vec2 &v2)
{
  float dot_product = v1.x * v2.x + v1.y * v2.y;
  return dot_product;
}
// Ordering of the vectors matter here because we are going with a
// left handed system, so this calculation below gives us the correct face normal towards
// our camera so that we can do proper back-face culling later
inline Vec3 vec3_cross(const Vec3 &v1, const Vec3 &v2)
{
  float x = v1.y * v2.z - v1.z * v2.y;
  float y = v1.z * v2.x - v1.x * v2.z;
  float z = v1.x * v2.y - v1.y * v2.x;
  Vec3 result(x, y, z);
  return result;
}

inline float vec3_dot(const Vec3 &v1, const Vec3 &v2)
{
  float dot_product = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
  return dot_product;
}

inline Vec3 vec3_mul(const Vec3 &v1, const float scalar)
{
  float x = v1.x * scalar;
  float y = v1.y * scalar;
  float z = v1.z * scalar;

  Vec3 result(x, y, z);
  return result;
}

inline Vec3 vec3_div(const Vec3 &v1, const float scalar)
{
  float x = v1.x / scalar;
  float y = v1.y / scalar;
  float z = v1.z / scalar;

  Vec3 result(x, y, z);
  return result;
}

inline Vec3 vec3_add(const Vec3 &v1, const Vec3 &v2)
{
  float x = v1.x + v2.x;
  float y = v1.y + v2.y;
  float z = v1.z + v2.z;
  Vec3 result(x, y, z);
  return result;
}

inline Vec3 vec3_sub(const Vec3 &v1, const Vec3 &v2)
{
  float x = v1.x - v2.x;
  float y = v1.y - v2.y;
  float z = v1.z - v2.z;
  Vec3 result(x, y, z);
  return result;
}
inline float vec3_length(const Vec3 &v)
{
  float x_squared = v.x * v.x;
  float y_squared = v.y * v.y;
  float z_squared = v.z * v.z;
  float vector_length = sqrtf(x_squared + y_squared + z_squared);
  return vector_length;
}
inline Vec3 vec3_get_normalized_vector(const Vec3 &v)
{
  Vec3 result_vector = v;
  float length = vec3_length(result_vector);
  result_vector.x /= length;
  result_vector.y /= length;
  result_vector.z /= length;
  return result_vector;
}

inline void vec3_normalize(Vec3 &v)
{
  float length = vec3_length(v);
  v.x /= length;
  v.y /= length;
  v.z /= length;
}

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
