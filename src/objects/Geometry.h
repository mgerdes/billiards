#ifndef BILLIARDS_GEOMETRY_H
#define BILLIARDS_GEOMETRY_H

#include "Vector3.h"

class Geometry {
    private:
        int numVertices, maxVertices;
        float *vertices;
    public:
        Geometry(int maxVertices);

        void addVertex(float x, float y, float z);

        int getNumVertices();

        float *getVertices();
};

#endif
