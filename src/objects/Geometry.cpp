#include "Geometry.h"

Geometry::Geometry(int maxVertices) {
    this->numVertices = 0;
    this->maxVertices = maxVertices;
    this->vertices = new float[maxVertices * 3];
}

void Geometry::addVertex(float x, float y, float z) {
    this->vertices[this->numVertices++] = x;
    this->vertices[this->numVertices++] = y;
    this->vertices[this->numVertices++] = z;
}

int Geometry::getNumVertices() {
    return this->numVertices;
}

float *Geometry::getVertices() {
    return this->vertices;
}
