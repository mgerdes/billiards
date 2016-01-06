#ifndef BILLIARDS_BOUNDINGOBJECT_H
#define BILLIARDS_BOUNDINGOBJECT_H

#include "Mesh.h"
#include "ResourceManager.h"

class RectangleBoundingObject {
private:
    static vector<Vector> rectangleVertices, rectangleNormals;

public:
    float x, y, width, height;
    Mesh mesh;

    RectangleBoundingObject(float x, float y, float width, float height);

    void draw();
};

class CircleBoundingObject {
private:
    static const int NUM_POINTS = 64;
    static vector<Vector> circleVertices, circleNormals;

    static vector<Vector> createCircleVertices();

    static vector<Vector> createCircleNormals();

public:
    float x, y, radius;
    Mesh mesh;

    CircleBoundingObject(float x, float y, float radius);

    void draw();
};

#endif //BILLIARDS_BOUNDINGOBJECT_H
