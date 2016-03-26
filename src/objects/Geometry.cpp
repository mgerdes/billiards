#include "Geometry.h"

Geometry::Geometry(int maxVertices) {
    this->numVertices = 0;
    this->maxVertices = maxVertices;
    this->vertices = new float[maxVertices * 3];
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

void Geometry::setNumTextureCoords(int maxNumTextureCoords) {
    this->numTextureCoords = 0;
    this->maxNumTextureCoords = maxNumTextureCoords;
    this->textureCoords = new float[maxNumTextureCoords * 3];
}

void Geometry::addTextureCoord(float x, float y, float z) {
    this->textureCoords[this->numTextureCoords * 3] = x;
    this->textureCoords[this->numTextureCoords * 3 + 1] = y;
    this->textureCoords[this->numTextureCoords * 3 + 2] = z;
    this->numTextureCoords++;
}
