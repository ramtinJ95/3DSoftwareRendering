#pragma once

#include "triangle.hpp"
#include "vector.hpp"
#include <string>
#include <vector>

inline constexpr int N_CUBE_VERTICES = 8;
inline constexpr int N_CUBE_FACES = (6 * 2); // 6 cube faces, 2 triangles per face

extern Vec3 cube_vertices[N_CUBE_VERTICES];
extern Face cube_faces[N_CUBE_FACES];

struct Mesh
{
  std::vector<Vec3> vertices;
  std::vector<Face> mesh_faces;
  Vec3 rotation;

  // Default constructor - rotation defaults to Vec3's default constructor
  Mesh() = default;

  // Constructor with rotation parameter (copy version)
  Mesh(const std::vector<Vec3> &vertices, const std::vector<Face> &faces,
       const Vec3 &rotation = Vec3{0, 0, 0})
      : vertices(vertices), mesh_faces(faces), rotation(rotation)
  {
  }

  // Constructor with rotation parameter (move version)
  Mesh(std::vector<Vec3> &&vertices, std::vector<Face> &&faces,
       const Vec3 &rotation = Vec3{0, 0, 0})
      : vertices(std::move(vertices)), mesh_faces(std::move(faces)), rotation(rotation)
  {
  }

  // Constructor with initializer lists and rotation
  Mesh(std::initializer_list<Vec3> vertices, std::initializer_list<Face> faces,
       const Vec3 &rotation = Vec3{0, 0, 0})
      : vertices(vertices), mesh_faces(faces), rotation(rotation)
  {
  }
};

extern Mesh mesh;

Mesh load_cube_mesh_data(void);
Mesh load_obj_file_data(std::string filepath);
