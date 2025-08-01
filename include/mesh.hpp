#pragma once

#include "triangle.hpp"
#include "vector.hpp"

inline constexpr int N_MESH_VERTICES = 8;
inline constexpr int N_MESH_FACES = (6 * 2); // 6 cube faces, 2 triangles per face

extern Vec3 mesh_vertices[N_MESH_VERTICES];
extern Face mesh_faces[N_MESH_FACES];
