#include "Mesh.h"

Mesh::Mesh(vector<Vector> verticesVector,
           vector<Vector> normalsVector,
           Material material,
           Shader &shader) : material(material),
                             shader(shader) {
    numberOfVertices = (int) verticesVector.size();

    GLfloat vertices[numberOfVertices * 3];
    GLfloat normals[numberOfVertices * 3];

    for (int i = 0; i < numberOfVertices; i++) {
        vertices[i * 3] = (GLfloat) verticesVector[i].x;
        vertices[i * 3 + 1] = (GLfloat) verticesVector[i].y;
        vertices[i * 3 + 2] = (GLfloat) verticesVector[i].z;

        normals[i * 3] = (GLfloat) normalsVector[i].x;
        normals[i * 3 + 1] = (GLfloat) normalsVector[i].y;
        normals[i * 3 + 2] = (GLfloat) normalsVector[i].z;
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

Mesh::Mesh(vector<Vector> verticesVector,
           vector<Vector> normalsVector,
           vector<Vector> textureCoordinatesVector,
           Material material,
           Shader &shader) : material(material),
                             shader(shader) {
    numberOfVertices = (int) verticesVector.size();

    GLfloat vertices[numberOfVertices * 3];
    GLfloat normals[numberOfVertices * 3];
    GLfloat textureCoords[numberOfVertices * 2];

    for (int i = 0; i < numberOfVertices; i++) {
        vertices[i * 3] = (GLfloat) verticesVector[i].x;
        vertices[i * 3 + 1] = (GLfloat) verticesVector[i].y;
        vertices[i * 3 + 2] = (GLfloat) verticesVector[i].z;

        normals[i * 3] = (GLfloat) normalsVector[i].x;
        normals[i * 3 + 1] = (GLfloat) normalsVector[i].y;
        normals[i * 3 + 2] = (GLfloat) normalsVector[i].z;

        textureCoords[i * 2] = (GLfloat) textureCoordinatesVector[i].x;
        textureCoords[i * 2 + 1] = (GLfloat) textureCoordinatesVector[i].y;
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

    GLuint texture_coords_vbo;
    glGenBuffers(1, &texture_coords_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, texture_coords_vbo);
    glBufferData(GL_ARRAY_BUFFER,
                 2 * numberOfVertices * sizeof (GLfloat),
                 textureCoords,
                 GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

void Mesh::draw() {
    shader.setMaterialProperty(material);
    shader.enable();
    material.texture.enable();

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, numberOfVertices);
    glBindVertexArray(0);

    material.texture.disable();
    shader.disable();
}
