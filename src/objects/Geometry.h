#ifndef BILLIARDS_GEOMETRY_H
#define BILLIARDS_GEOMETRY_H

#include "Vector3.h"

class Geometry {
    private:
        int numVertices, maxVertices;
        float *vertices;

        int numTextureCoords, maxNumTextureCoords;
        float *textureCoords;

        int numNormals, maxNumNormals;
        float *normals;
    public:
        Geometry(int maxVertices);

        void addVertex(float x, float y, float z);

        int getNumVertices();

        float *getVertices();

        void setMaxNumTextureCoords(int maxNumTextureCoords);

        void addTextureCoord(float x, float y);

        int getNumTextureCoords();

        float *getTextureCoords();

        bool hasTextureCoords();

        void setMaxNumNormals(int maxNumNormals);

        void addNormal(float x, float y, float z);

        int getNumNormals();

        float *getNormals();

        bool hasNormals();
};

#endif
