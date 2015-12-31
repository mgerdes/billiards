#include "Mesh.h"

Mesh::Mesh(vector<Vec> vertices, const Shader &_shader) : shader(_shader) {
    numberOfVertices = (int) vertices.size();

    GLfloat positions[numberOfVertices * 3];

    for (int i = 0; i < numberOfVertices; i++) {
        positions[i * 3] = (GLfloat) vertices[i].x;
        positions[i * 3 + 1] = (GLfloat) vertices[i].y;
        positions[i * 3 + 2] = (GLfloat) vertices[i].z;
    }

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint positions_vbo;
    glGenBuffers(1, &positions_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, positions_vbo);
    glBufferData(GL_ARRAY_BUFFER,
                 3 * numberOfVertices * sizeof(GLfloat),
                 positions,
                 GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

void Mesh::draw() {
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, numberOfVertices);
    glBindVertexArray(0);
}
