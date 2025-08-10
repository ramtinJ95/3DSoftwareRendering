#include "mesh.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

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
    Face(1, 2, 3), Face(1, 3, 4),
    // right
    Face(4, 3, 5), Face(4, 5, 6),
    // back
    Face(6, 5, 7), Face(6, 7, 8),
    // left
    Face(8, 7, 2), Face(8, 2, 1),
    // top
    Face(2, 7, 5), Face(2, 5, 3),
    // bottom
    Face(6, 8, 1), Face(6, 1, 4)};

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
  std::ifstream file(filepath);
  if (!file.is_open())
  {
    std::cerr << "Error: Could not open the file.\n";
    Mesh empty_mesh;
    return empty_mesh; // this is garbage code
  }

  std::vector<Vec3> vertices;
  std::string line;

  while (std::getline(file, line))
  {
    if (line.empty())
      continue;

    std::istringstream iss(line);
    std::string prefix;
    iss >> prefix;

    if (prefix == "v")
    {
      int x, y, z;
      iss >> x >> y >> z;
      Vec3 v(x, y, z);
      vertices.push_back(v);
    }

    if (prefix == "f")
    {
    }
  }

  // 4. Close the file
  file.close();

  Mesh random_mesh;
  return random_mesh;
}
