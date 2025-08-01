#include "mesh.hpp"

Vec3 mesh_vertices[N_MESH_VERTICES] = {
    Vec3(-1, -1, -1), // 1
    Vec3(-1, 1, -1),  // 2
    Vec3(1, 1, -1),   // 3
    Vec3(1, -1, -1),  // 4
    Vec3(1, 1, 1),    // 5
    Vec3(1, -1, 1),   // 6
    Vec3(-1, 1, 1),   // 7
    Vec3(-1, -1, 1)   // 8
};

Face mesh_faces[N_MESH_FACES] = {
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
