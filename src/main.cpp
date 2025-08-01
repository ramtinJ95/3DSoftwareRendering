#include "display.hpp"
#include "vector.hpp"
#include <SDL_timer.h>

const int N_POINTS = 9 * 9 * 9;
Vec3 cube_points[N_POINTS];
Vec2 projected_points[N_POINTS];

const Vec3 camera_position(0, 0, -5);
Vec3 cube_rotation(0, 0, 0);

float fov_factor = 640;

bool is_running = false;
int previous_frame_time = 0;

void setup(void)
{
  // Allocate the memory in bytes to hold color buffer
  color_buffer = (uint32_t *)malloc(sizeof(uint32_t) * WINDOW_WIDTH * WINDOW_HEIGHT);

  // Creating a SDL texture that is used to display the color buffer
  color_buffer_texture = SDL_CreateTexture(
      renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, WINDOW_WIDTH, WINDOW_HEIGHT);

  // Array of vectors for cube showcase
  // TODO: remove this garbage
  int count = 0;
  for (float x = -1; x <= 1; x += 0.25)
  {

    for (float y = -1; y <= 1; y += 0.25)
    {

      for (float z = -1; z <= 1; z += 0.25)
      {
        Vec3 new_point(x, y, z);
        cube_points[count++] = new_point;
      }
    }
  }
}

void process_input(void)
{
  SDL_Event event;
  SDL_PollEvent(&event);

  switch (event.type)
  {
  case SDL_QUIT:
    is_running = false;
    break;
  case SDL_KEYDOWN:
    if (event.key.keysym.sym == SDLK_ESCAPE)
      is_running = false;
    break;
  }
}

// Function that receives 3D vector and return projected 2D point
Vec2 project(Vec3 point)
{
  Vec2 projected_point(fov_factor * point.x / point.z, fov_factor * point.y / point.z);
  return projected_point;
}

void update(void)
{
  int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks64() - previous_frame_time);

  if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME)
  {
    SDL_Delay(time_to_wait);
  }

  previous_frame_time = SDL_GetTicks();
  cube_rotation.x += 0.01;
  cube_rotation.y += 0.01;
  cube_rotation.z += 0.01;

  for (int i = 0; i < N_POINTS; i++)
  {
    Vec3 point = cube_points[i];
    Vec3 transformed_point = vec3_rotate_x(&point, cube_rotation.x);
    transformed_point = vec3_rotate_y(&transformed_point, cube_rotation.y);
    transformed_point = vec3_rotate_z(&transformed_point, cube_rotation.z);
    transformed_point.z -= camera_position.z;
    Vec2 projected_point = project(transformed_point);
    projected_points[i] = projected_point;
  }
}

void render(void)
{
  // draw_grid(10, 0xFF333333);

  const float translate_amount_x = WINDOW_WIDTH / 2;
  const float translate_amount_y = WINDOW_HEIGHT / 2;
  for (int i = 0; i < N_POINTS; i++)
  {
    Vec2 projected_point = projected_points[i];
    draw_rectangle(projected_point.x + translate_amount_x, projected_point.y + translate_amount_y,
                   4, 4, 0xFFFF0000);
  }

  render_color_buffer();
  clear_color_buffer_SIMD(color_buffer, WINDOW_WIDTH, WINDOW_HEIGHT, 0xFF000000);

  SDL_RenderPresent(renderer);
}

int main(void)
{
  is_running = initialize_window();

  setup();

  while (is_running)
  {
    process_input();
    update();
    render();
  }

  return 0;
}
