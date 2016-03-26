#ifndef BILLIARDS_GEOMETRY_H
#define BILLIARDS_GEOMETRY_H

#include "Vector3.h"

class Geometry {
    private:
        int numVertices, maxVertices, numTextureCoords, maxNumTextureCoords;
        float *vertices, *textureCoords;
    public:
        Geometry(int maxVertices);

        void addVertex(float x, float y, float z);

        int getNumVertices();

        float *getVertices();

        void setNumTextureCoords(int maxNumTextureCoords);

        void addTextureCoord(float x, float y);

        int getNumTextureCoords();

        float *getTextureCoords();
};

#endif
