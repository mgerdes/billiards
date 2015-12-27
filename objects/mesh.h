#ifndef MESH_H
#define MESH_H

#include <assimp/cimport.h>
#include <stdlib.h>
#include <GL/glew.h>
#include "camera.h"
#include "maths.h"

typedef struct Material {
    Vec* diffuse_color;
    Vec* ambient_color;
    Vec* specular_color;
} Material;

typedef struct Texture {
    GLuint id;
} Texture;

typedef struct Vertex {
    Vec* position;
    Vec* normal;
    Vec* texture_coords;
} Vertex;

typedef struct Mesh {
    GLuint vao;
    int num_vertices;
    Texture* texture;
    Material* material;
} Mesh;

Mesh* create_mesh(Vertex** vertices, int num_vertices, Texture* texture, Material* material);
void draw_mesh(Mesh* mesh, GLint shader_program);

#endif
