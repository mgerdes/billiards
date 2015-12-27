#include "mesh.h"

Mesh* create_mesh(Vertex** vertices, int num_vertices, Texture* texture, Material* material) {
    GLfloat* positions = (GLfloat*) malloc(num_vertices * 3 * sizeof(GLfloat));
    GLfloat* normals = (GLfloat*) malloc(num_vertices * 3 * sizeof(GLfloat));
    GLfloat* texture_coords = (GLfloat*) malloc(num_vertices * 2 * sizeof(GLfloat));

    for (int i = 0; i < num_vertices; i++) {
        positions[i * 3] = vertices[i]->position->x;
        positions[i * 3 + 1] = vertices[i]->position->y;
        positions[i * 3 + 2] = vertices[i]->position->z;

        normals[i * 3] = vertices[i]->normal->x;
        normals[i * 3 + 1] = vertices[i]->normal->y;
        normals[i * 3 + 2] = vertices[i]->normal->z;

        if (vertices[i]->texture_coords) {
            texture_coords[i * 2] = vertices[i]->texture_coords->x;
            texture_coords[i * 2 + 1] = vertices[i]->texture_coords->y;
        } else {
            texture_coords[i * 2] = 0;
            texture_coords[i * 2 + 1] = 0;
        }
    }

    GLuint mesh_vao;
    glGenVertexArrays(1, &mesh_vao);
    glBindVertexArray(mesh_vao);

    GLuint positions_vbo;
    glGenBuffers(1, &positions_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, positions_vbo);
    glBufferData(GL_ARRAY_BUFFER,
            3 * num_vertices * sizeof (GLfloat),
            positions,
            GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

    GLuint normals_vbo;
    glGenBuffers(1, &normals_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, normals_vbo);
    glBufferData(GL_ARRAY_BUFFER,
            3 * num_vertices * sizeof (GLfloat),
            normals,
            GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(1);

    GLuint texture_coords_vbo;
    glGenBuffers(1, &texture_coords_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, texture_coords_vbo);
    glBufferData(GL_ARRAY_BUFFER,
                 2 * num_vertices * sizeof (GLfloat),
                 texture_coords,
                 GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);

    Mesh* mesh = malloc(sizeof(Mesh));
    mesh->vao = mesh_vao;
    mesh->num_vertices = num_vertices;
    mesh->texture = texture;
    mesh->material = material;
    return mesh;
}

void draw_mesh(Mesh* mesh, GLint shader_program) {
    GLint material_diffuse = glGetUniformLocation(shader_program, "material.diffuse_color");
    GLint material_ambient = glGetUniformLocation(shader_program, "material.ambient_color");
    GLint material_specular  = glGetUniformLocation(shader_program, "material.specular_color");
    GLint material_shininess = glGetUniformLocation(shader_program, "material.shininess");

    glUniform3f(material_diffuse,
                (GLfloat) mesh->material->diffuse_color->x,
                (GLfloat) mesh->material->diffuse_color->y,
                (GLfloat) mesh->material->diffuse_color->z);
    glUniform3f(material_ambient,
                (GLfloat) mesh->material->ambient_color->x,
                (GLfloat) mesh->material->ambient_color->y,
                (GLfloat) mesh->material->ambient_color->z);
    glUniform3f(material_specular,
                (GLfloat) mesh->material->specular_color->x,
                (GLfloat) mesh->material->specular_color->y,
                (GLfloat) mesh->material->specular_color->z);
    glUniform1f(material_shininess, 32.0f);

    glBindTexture(GL_TEXTURE_2D, mesh->texture->id);
    glBindVertexArray(mesh->vao);
    glDrawArrays(GL_TRIANGLES, 0, mesh->num_vertices);
    glBindVertexArray(0);
}
