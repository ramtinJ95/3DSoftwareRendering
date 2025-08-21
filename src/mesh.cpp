#include "mesh.hpp"
#include "vector.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

Mesh mesh;

Vec3 cube_vertices[N_CUBE_VERTICES] = {
    Vec3(-1, -1, -1), // 1
    Vec3(-1, 1, -1),  // 2
    Vec3(1, 1, -1),   // 3
    Vec3(1, -1, -1),  // 4
    Vec3(1, 1, 1),    // 5
    Vec3(1, -1, 1),   // 6
    Vec3(-1, 1, 1),   // 7
    Vec3(-1, -1, 1)   // 8
};

Face cube_faces[N_CUBE_FACES] = {
    // front
    Face(1, 2, 3, 0xFFFF0000), Face(1, 3, 4, 0xFFFF0000),
    // right
    Face(4, 3, 5, 0xFF00FF00), Face(4, 5, 6, 0xFF00FF00),
    // back
    Face(6, 5, 7, 0xFF0000FF), Face(6, 7, 8, 0xFF0000FF),
    // left
    Face(8, 7, 2, 0xFFFFFF00), Face(8, 2, 1, 0xFFFFFF00),
    // top
    Face(2, 7, 5, 0xFFFF00FF), Face(2, 5, 3, 0xFFFF00FF),
    // bottom
    Face(6, 8, 1, 0xFF00FFFF), Face(6, 1, 4, 0xFF00FFFF)};

Mesh load_cube_mesh_data(void)
{
  std::vector<Vec3> cube_vertices_temp;
  std::vector<Face> cube_faces_temp;
  for (int i = 0; i < N_CUBE_VERTICES; i++)
  {
    cube_vertices_temp.push_back(cube_vertices[i]);
  }
  for (int i = 0; i < N_CUBE_FACES; i++)
  {
    cube_faces_temp.push_back(cube_faces[i]);
  }
  Mesh mesh(std::move(cube_vertices_temp), std::move(cube_faces_temp), Vec3{0, 0, 0});
  return mesh;
}

Mesh load_obj_file_data(std::string filepath)
{
  std::vector<Vec3> vertices;
  std::vector<Face> faces;
  std::ifstream ifs(filepath);
  std::string line;
  while (std::getline(ifs, line))
  {
    std::istringstream iss(line);
    std::string token;

    iss >> token;
    if (token == "v")
    {
      Vec3 v;
      iss >> v.x >> v.y >> v.z;
      vertices.push_back(v);
    }
    else if (token == "f")
    {
      Face f;
      iss >> f.a >> token >> f.b >> token >> f.c;
      faces.push_back(f);
    }
  }
  Mesh mesh(std::move(vertices), std::move(faces));
  return mesh;
}
