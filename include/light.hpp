#pragma once
#include "vector.hpp"
struct Light
{
  Vec3 direction;
  // initialize with a direction vector at 0,0,0
  Light() : direction(Vec3(0, 0, 0))
  {
  }
  Light(Vec3 dir) : direction(dir)
  {
  }
};

extern Light light;

uint32_t apply_light_intensity(uint32_t color, float light_intensity_factor);
