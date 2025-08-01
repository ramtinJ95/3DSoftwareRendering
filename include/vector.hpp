#pragma once

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
