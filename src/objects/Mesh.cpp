#include "Mesh.h"

Mesh::Mesh(Geometry *geometry, Material *material) {
    this->geometry = geometry;
    this->material = material;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int verticesVBO;
    glGenBuffers(1, &verticesVBO);
    glBindBuffer(GL_ARRAY_BUFFER, verticesVBO);
    glBufferData(GL_ARRAY_BUFFER,
            3 * geometry->getNumVertices() * sizeof(float),
            geometry->getVertices(),
            GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

void Mesh::draw() {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, geometry->getNumVertices());
    glBindVertexArray(0);
}

Material *Mesh::getMaterial() {
    return material;
}
