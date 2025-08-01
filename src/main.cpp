#include "display.hpp"
#include "mesh.hpp"
#include "triangle.hpp"
#include "vector.hpp"
#include <SDL_timer.h>

Triangle triangles_to_render[N_MESH_FACES];

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

  for (int i = 0; i < N_MESH_FACES; i++)
  {
    Face mesh_face = mesh_faces[i];
    Vec3 face_vertices[3];
    face_vertices[0] = mesh_vertices[mesh_face.a - 1];
    face_vertices[1] = mesh_vertices[mesh_face.b - 1];
    face_vertices[2] = mesh_vertices[mesh_face.c - 1];

    Triangle projected_triangle;

    for (int j = 0; j < 3; j++)
    {
      Vec3 transformed_vertex = face_vertices[j];
      transformed_vertex = vec3_rotate_x(&transformed_vertex, cube_rotation.x);
      transformed_vertex = vec3_rotate_y(&transformed_vertex, cube_rotation.y);
      transformed_vertex = vec3_rotate_z(&transformed_vertex, cube_rotation.z);

      // Translate the vertex away from the camera
      transformed_vertex.z -= camera_position.z;

      Vec2 projected_point = project(transformed_vertex);

      // scale and translate the projected vertices to the middle of the screen
      projected_point.x += WINDOW_WIDTH / 2;
      projected_point.y += WINDOW_HEIGHT / 2;

      projected_triangle.points[j] = projected_point;
    }
    triangles_to_render[i] = projected_triangle;
  }

  cube_rotation.x += 0.01;
  cube_rotation.y += 0.01;
  cube_rotation.z += 0.01;
}

void render(void)
{
  // draw_grid(10, 0xFF333333);

  for (int i = 0; i < N_MESH_FACES; i++)
  {
    Triangle triangle = triangles_to_render[i];
    draw_rectangle(triangle.points[0].x, triangle.points[0].y, 3, 3, 0xFFFF0000);
    draw_rectangle(triangle.points[1].x, triangle.points[1].y, 3, 3, 0xFFFF0000);
    draw_rectangle(triangle.points[2].x, triangle.points[2].y, 3, 3, 0xFFFF0000);

    draw_triangle(triangle.points[0].x, triangle.points[0].y, triangle.points[1].x,
                  triangle.points[1].y, triangle.points[2].x, triangle.points[2].y, 0xFFFF0000);
  }
  draw_line(100, 200, 150, 250, 0xFFFF0000);

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
