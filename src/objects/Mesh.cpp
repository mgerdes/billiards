#include "Mesh.h"

Mesh::Mesh(vector<Vector> vertices_vector,
           vector<Vector> normals_vector,
           Material material,
           Shader &shader) : material(material),
                             shader(shader) {
    numberOfVertices = (int) vertices_vector.size();

    GLfloat vertices[numberOfVertices * 3];
    GLfloat normals[numberOfVertices * 3];

    for (int i = 0; i < numberOfVertices; i++) {
        vertices[i * 3] = (GLfloat) vertices_vector[i].x;
        vertices[i * 3 + 1] = (GLfloat) vertices_vector[i].y;
        vertices[i * 3 + 2] = (GLfloat) vertices_vector[i].z;

        normals[i * 3] = (GLfloat) normals_vector[i].x;
        normals[i * 3 + 1] = (GLfloat) normals_vector[i].y;
        normals[i * 3 + 2] = (GLfloat) normals_vector[i].z;
    }

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vertices_vbo;
    glGenBuffers(1, &vertices_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vertices_vbo);
    glBufferData(GL_ARRAY_BUFFER,
                 3 * numberOfVertices * sizeof(GLfloat),
                 vertices,
                 GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

    GLuint normals_vbo;
    glGenBuffers(1, &normals_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, normals_vbo);
    glBufferData(GL_ARRAY_BUFFER,
            3 * numberOfVertices * sizeof (GLfloat),
            normals,
            GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void Mesh::draw() {
    shader.setMaterialProperty(material);

    shader.enable();

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, numberOfVertices);
    glBindVertexArray(0);

    shader.disable();
}
