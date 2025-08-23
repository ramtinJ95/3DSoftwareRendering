#include "display.hpp"
#include "matrix.hpp"
#include "mesh.hpp"
#include "triangle.hpp"
#include "vector.hpp"
#include <vector>

// Triangle triangles_to_render[N_MESH_FACES];
std::vector<Triangle> triangles_to_render;

const Vec3 camera_position(0, 0, 0);
const int CAMERA_ZOOM = 7;

using enum Render_method;
using enum Cull_method;

Render_method render_method;
Cull_method cull_method;

float fov_factor = 640;

bool is_running = false;
int previous_frame_time = 0;

void setup(void)
{

  render_method = render_wire;
  cull_method = cull_backface;
  // Allocate the memory in bytes to hold color buffer
  color_buffer = (uint32_t *)malloc(sizeof(uint32_t) * WINDOW_WIDTH * WINDOW_HEIGHT);

  // Creating a SDL texture that is used to display the color buffer
  color_buffer_texture = SDL_CreateTexture(
      renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, WINDOW_WIDTH, WINDOW_HEIGHT);
  // mesh = load_obj_file_data("assets/f22.obj");
  mesh = load_cube_mesh_data();
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
    if (event.key.keysym.sym == SDLK_1)
      render_method = render_wire_vertex;
    if (event.key.keysym.sym == SDLK_2)
      render_method = render_wire;
    if (event.key.keysym.sym == SDLK_3)
      render_method = render_fill_triangle;
    if (event.key.keysym.sym == SDLK_4)
      render_method = render_fill_triangle_wire;
    if (event.key.keysym.sym == SDLK_c)
      cull_method = cull_backface;
    if (event.key.keysym.sym == SDLK_d)
      cull_method = cull_none;
    break;
  }
}

// Function that receives 3D vector and return projected 2D point
Vec2 project(Vec3 point)
{
  Vec2 projected_point(fov_factor * point.x / point.z, -fov_factor * point.y / point.z);
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
  // mesh.rotation.y += 0.01;
  // mesh.rotation.z += 0.01;

  // mesh.scale.x += 0.002;
  // mesh.scale.y += 0.001;
  //
  mesh.translation.x += 0.01;
  mesh.translation.z = CAMERA_ZOOM;

  Mat4 scale_matrix = mat4_make_scale(mesh.scale.x, mesh.scale.y, mesh.scale.z);
  Mat4 translation_matrix =
      mat4_make_translation(mesh.translation.x, mesh.translation.y, mesh.translation.z);
  Mat4 rotation_x_matrix = mat4_make_rotation_x(mesh.rotation.x);
  Mat4 rotation_y_matrix = mat4_make_rotation_y(mesh.rotation.y);
  Mat4 rotation_z_matrix = mat4_make_rotation_z(mesh.rotation.z);

  for (int i = 0; i < num_faces; i++)
  {
    Face mesh_face = mesh.mesh_faces[i];

    Vec3 face_vertices[3];
    face_vertices[0] = mesh.vertices[mesh_face.a - 1];
    face_vertices[1] = mesh.vertices[mesh_face.b - 1];
    face_vertices[2] = mesh.vertices[mesh_face.c - 1];

    Vec4 transformed_vertices[3];

    for (int j = 0; j < 3; j++)
    {
      Vec4 transformed_vertex = vec3_to_vec4(face_vertices[j]);

      // create world matrix by multiplying matrices in the correct order
      Mat4 world_matrix = mat4_identity();

      // multiply all matrices
      world_matrix = mat4_mul_mat4(scale_matrix, world_matrix);
      world_matrix = mat4_mul_mat4(rotation_x_matrix, world_matrix);
      world_matrix = mat4_mul_mat4(rotation_y_matrix, world_matrix);
      world_matrix = mat4_mul_mat4(rotation_z_matrix, world_matrix);
      world_matrix = mat4_mul_mat4(translation_matrix, world_matrix);
      // world times original vector
      transformed_vertex = mat4_mul_vec4(world_matrix, transformed_vertex);

      transformed_vertices[j] = transformed_vertex;
    }
    // check back face culling before projecting
    if (cull_method == cull_backface)
    {
      // if the face is not visible then we skip it
      Vec3 vector_a = vec4_to_vec3(transformed_vertices[0]);
      Vec3 vector_b = vec4_to_vec3(transformed_vertices[1]);
      Vec3 vector_c = vec4_to_vec3(transformed_vertices[2]);

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
    }

    // performing the projection
    Vec2 projected_points[3];
    for (int j = 0; j < 3; j++)
    {
      projected_points[j] = project(vec4_to_vec3(transformed_vertices[j]));
      // scale and translate the projected vertices to the middle of the screen
      projected_points[j].x += WINDOW_WIDTH / 2;
      projected_points[j].y += WINDOW_HEIGHT / 2;
    }

    float z_average =
        (transformed_vertices[0].z + transformed_vertices[1].z + transformed_vertices[2].z) / 3.0f;

    Triangle projected_triangle(projected_points[0], projected_points[1], projected_points[2],
                                mesh_face.color);
    projected_triangle.z_average = z_average;
    triangles_to_render.push_back(projected_triangle);
  }
  std::sort(triangles_to_render.begin(), triangles_to_render.end(),
            [](const Triangle &a, const Triangle &b) { return a.z_average > b.z_average; });
}

void render(void)
{
  // draw_grid(10, 0xFF333333);

  for (const Triangle &triangle : triangles_to_render)
  {
    // draw filled triangle
    if (render_method == render_fill_triangle || render_method == render_fill_triangle_wire)
    {
      draw_filled_triangle(triangle.points[0].x, triangle.points[0].y, triangle.points[1].x,
                           triangle.points[1].y, triangle.points[2].x, triangle.points[2].y,
                           triangle.color);
    }
    // draw triangle wireframe
    if (render_method == render_wire || render_method == render_wire_vertex ||
        render_method == render_fill_triangle_wire)
    {
      draw_triangle(triangle.points[0].x, triangle.points[0].y, triangle.points[1].x,
                    triangle.points[1].y, triangle.points[2].x, triangle.points[2].y, 0xFFFFFFFF);
    }
    // draw triangle vertex points
    if (render_method == render_wire_vertex)
    {
      draw_rectangle(triangle.points[0].x - 3, triangle.points[0].y - 3, 6, 6, 0xFFFF0000);
      draw_rectangle(triangle.points[1].x - 3, triangle.points[1].y - 3, 6, 6, 0xFFFF0000);
      draw_rectangle(triangle.points[2].x - 3, triangle.points[2].y - 3, 6, 6, 0xFFFF0000);
    }
  }

  render_color_buffer();
  clear_color_buffer_SIMD(color_buffer, WINDOW_WIDTH, WINDOW_HEIGHT, 0xFF000000);

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
