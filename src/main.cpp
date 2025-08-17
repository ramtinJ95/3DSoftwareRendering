#include "display.hpp"
#include "mesh.hpp"
#include "triangle.hpp"
#include "vector.hpp"
#include <vector>

// Triangle triangles_to_render[N_MESH_FACES];
std::vector<Triangle> triangles_to_render;

const Vec3 camera_position(0, 0, 0);

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
  mesh = load_obj_file_data("assets/f22.obj");
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
  int num_faces = mesh.mesh_faces.size();
  mesh.rotation.x += 0.01;
  mesh.rotation.y += 0.00;
  mesh.rotation.z += 0.00;

  for (int i = 0; i < num_faces; i++)
  {
    Face mesh_face = mesh.mesh_faces[i];

    Vec3 face_vertices[3];
    face_vertices[0] = mesh.vertices[mesh_face.a - 1];
    face_vertices[1] = mesh.vertices[mesh_face.b - 1];
    face_vertices[2] = mesh.vertices[mesh_face.c - 1];

    Triangle projected_triangle;

    Vec3 transformed_vertices[3];

    for (int j = 0; j < 3; j++)
    {
      Vec3 transformed_vertex = face_vertices[j];
      transformed_vertex = vec3_rotate_x(&transformed_vertex, mesh.rotation.x);
      transformed_vertex = vec3_rotate_y(&transformed_vertex, mesh.rotation.y);
      transformed_vertex = vec3_rotate_z(&transformed_vertex, mesh.rotation.z);

      // Translate the vertex away from the camera
      transformed_vertex.z += 5;

      transformed_vertices[j] = transformed_vertex;
    }
    // check back face culling before projecting
    Vec3 vector_a = transformed_vertices[0];
    Vec3 vector_b = transformed_vertices[1];
    Vec3 vector_c = transformed_vertices[2];

    Vec3 v1 = vec3_sub(vector_b, vector_a);
    Vec3 v2 = vec3_sub(vector_c, vector_a);

    Vec3 normal = vec3_cross(v1, v2);
    Vec3 camera_ray = vec3_sub(camera_position, vector_a);

    float dot_product = vec3_dot(normal, camera_ray);

    // if dot product is negative then the face is pointing away from the
    // camera so we bypass the triangle entirely so we can save rendering cycles
    if (dot_product < 0)
    {
      continue;
    }

    // performing the projection
    for (int j = 0; j < 3; j++)
    {
      Vec2 projected_point = project(transformed_vertices[j]);
      // scale and translate the projected vertices to the middle of the screen
      projected_point.x += WINDOW_WIDTH / 2;
      projected_point.y += WINDOW_HEIGHT / 2;

      projected_triangle.points[j] = projected_point;
    }
    // triangles_to_render[i] = projected_triangle;
    triangles_to_render.push_back(projected_triangle);
  }
}

void render(void)
{
  // draw_grid(10, 0xFF333333);

  // for (const Triangle &triangle : triangles_to_render)
  // {
  //   // Triangle triangle = triangles_to_render[i];
  //   draw_rectangle(triangle.points[0].x, triangle.points[0].y, 3, 3, 0xFFFF0000);
  //   draw_rectangle(triangle.points[1].x, triangle.points[1].y, 3, 3, 0xFFFF0000);
  //   draw_rectangle(triangle.points[2].x, triangle.points[2].y, 3, 3, 0xFFFF0000);
  //
  //   draw_triangle(triangle.points[0].x, triangle.points[0].y, triangle.points[1].x,
  //                 triangle.points[1].y, triangle.points[2].x, triangle.points[2].y, 0xFFFF0000);
  // }
  //
  render_color_buffer();
  clear_color_buffer(0xFF000000);
  draw_triangle(300, 100, 50, 400, 500, 700, 0xFF00FF00);
  // clear_color_buffer_SIMD(color_buffer, WINDOW_WIDTH, WINDOW_HEIGHT, 0xFF000000);

  SDL_RenderPresent(renderer);
  triangles_to_render.clear();
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
