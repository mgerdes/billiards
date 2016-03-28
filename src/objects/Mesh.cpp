#include "Mesh.h"

Mesh::Mesh(Geometry *geometry, Material *material) : Object3D(0) {
    this->isMesh = true;   

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

    if (geometry->hasNormals()) {
        unsigned int normalsVBO;
        glGenBuffers(1, &normalsVBO);
        glBindBuffer(GL_ARRAY_BUFFER, normalsVBO);
        glBufferData(GL_ARRAY_BUFFER,
                3 * geometry->getNumNormals() * sizeof(float),
                geometry->getNormals(),
                GL_STATIC_DRAW);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        glEnableVertexAttribArray(1);
    }

    if (geometry->hasTextureCoords()) {
        unsigned int textureCoordsVBO;
        glGenBuffers(1, &textureCoordsVBO);
        glBindBuffer(GL_ARRAY_BUFFER, textureCoordsVBO);
        glBufferData(GL_ARRAY_BUFFER,
                2 * geometry->getNumTextureCoords() * sizeof(float),
                geometry->getTextureCoords(),
                GL_STATIC_DRAW);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);
        glEnableVertexAttribArray(2);
    } 

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

Geometry *Mesh::getGeometry() {
    return geometry;
}
