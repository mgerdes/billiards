#ifndef BILLIARDS_BOUNDINGOBJECT_H
#define BILLIARDS_BOUNDINGOBJECT_H

#include "Mesh.h"
#include "ResourceManager.h"

class RectangleBoundingObject {
private:
    float x, y, width, height;
    static vector<Vector> rectangleVertices, rectangleNormals;

public:
    Mesh mesh;

    RectangleBoundingObject(float x, float y, float width, float height);

    void draw();
};

class CircleBoundingObject {
private:
    static const int NUM_POINTS = 64;
    float x, y, radius;
    static vector<Vector> circleVertices, circleNormals;

    static vector<Vector> createCircleVertices();

    static vector<Vector> createCircleNormals();

public:
    Mesh mesh;

    CircleBoundingObject(float x, float y, float radius);

    void draw();
};

#endif //BILLIARDS_BOUNDINGOBJECT_H
