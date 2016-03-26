#include "Geometry.h"
#include "stdio.h"

Geometry::Geometry(int maxVertices) {
    this->numVertices = 0;
    this->maxVertices = maxVertices;
    this->vertices = new float[maxVertices * 3];

    this->numTextureCoords = 0;
    this->maxNumTextureCoords = 0;
    this->textureCoords = 0;
}

void Geometry::addVertex(float x, float y, float z) {
    this->vertices[this->numVertices * 3] = x;
    this->vertices[this->numVertices * 3 + 1] = y;
    this->vertices[this->numVertices * 3 + 2] = z;
    this->numVertices++;
}

int Geometry::getNumVertices() {
    return this->numVertices;
}

float *Geometry::getVertices() {
    return this->vertices;
}

void Geometry::setMaxNumTextureCoords(int maxNumTextureCoords) {
    this->numTextureCoords = 0;
    this->maxNumTextureCoords = maxNumTextureCoords;
    this->textureCoords = new float[maxNumTextureCoords * 2];
}

void Geometry::addTextureCoord(float x, float y) {
    this->textureCoords[this->numTextureCoords * 2] = x;
    this->textureCoords[this->numTextureCoords * 2 + 1] = y;
    this->numTextureCoords++;
}

int Geometry::getNumTextureCoords() {
    return this->numTextureCoords;
}

float *Geometry::getTextureCoords() {
    return this->textureCoords;
}

bool Geometry::hasTextureCoords() {
    return this->numTextureCoords > 0;
}

void Geometry::setMaxNumNormals(int maxNumNormals) {
    this->numNormals = 0;
    this->maxNumNormals = maxNumNormals;
    this->normals = new float[maxNumNormals * 3];
}

float *Geometry::getNormals() {
    return this->normals;
}

int Geometry::getNumNormals() {
    return this->numNormals;
}

void Geometry::addNormal(float x, float y, float z) {
    this->normals[this->numNormals * 3] = x;
    this->normals[this->numNormals * 3 + 1] = y;
    this->normals[this->numNormals * 3 + 2] = z;
    this->numNormals++;
}

bool Geometry::hasNormals() {
    return this->numNormals > 0;
}
