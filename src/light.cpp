#include "light.hpp"
#include "vector.hpp"

// global light only in z
Light light = Light(vec3_get_normalized_vector(Vec3(0, 0, 1)));

uint32_t apply_light_intensity(uint32_t color, float light_intensity_factor)
{
  // clamp light intensity factor between 0 and 1
  if (light_intensity_factor < 0)
    light_intensity_factor = 0;
  if (light_intensity_factor > 1)
    light_intensity_factor = 1;

  uint32_t a = (color & 0xFF000000);
  uint32_t r = (color & 0x00FF0000) * light_intensity_factor;
  uint32_t g = (color & 0x0000FF00) * light_intensity_factor;
  uint32_t b = (color & 0x000000FF) * light_intensity_factor;

  uint32_t new_color = a | (r & 0x00FF0000) | (g & 0x0000FF00) | (b & 0x000000FF);
  return new_color;
}
