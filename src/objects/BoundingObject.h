#ifndef BILLIARDS_BOUNDINGOBJECT_H
#define BILLIARDS_BOUNDINGOBJECT_H

#include "Mesh.h"
#include "ResourceManager.h"

class RectangleBoundingObject {
private:
    float x, y, width, height;

    static vector<Vector> getRectangleVertices(float x, float y, float width, float height);

    static vector<Vector> getRectangleNormals();

public:
    Mesh mesh;

    RectangleBoundingObject(float x, float y, float width, float height);

    void draw();
};

class CircleBoundingObject {
private:
    static const int NUM_POINTS = 64;

    float x, y, radius;

    static vector<Vector> getCircleVertices(float x, float y, float radius);

    static vector<Vector> getCircleNormals();

public:
    Mesh mesh;

    CircleBoundingObject(float x, float y, float radius);

    void draw();
};

#endif //BILLIARDS_BOUNDINGOBJECT_H
