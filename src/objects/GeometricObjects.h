#ifndef BILLIARDS_GEOMETRICOBJECTS_H
#define BILLIARDS_GEOMETRICOBJECTS_H

#include <vector>
#include "Vector.h"

class GeometricObjects {
public:
    static vector<Vector> getTriangleVertices() {
        return {Vector(0, 1, 0),
                Vector(-1, -1, 0),
                Vector(1, -1, 0)};
    }

    static vector<Vector> getSquareVertices() {
        return {Vector(1, 1, 0),
                Vector(-1, 1, 0),
                Vector(-1, -1, 0),
                Vector(-1, -1, 0),
                Vector(1, -1, 0),
                Vector(1, 1, 0)};
    }

    static vector<Vector> getCubeVertices() {
        return {Vector(1.0, -1.0, 1.0),
                Vector(-1.0, -1.0, -1.0),
                Vector(1.0, -1.0, -1.0),
                Vector(1.0, -1.0, 1.0),
                Vector(-1.0, -1.0, 1.0),
                Vector(-1.0, -1.0, -1.0),

                Vector(1.0, 1.0, -1.0),
                Vector(-1.0, -1.0, -1.0),
                Vector(1.0, -1.0, -1.0),
                Vector(1.0, 1.0, -1.0),
                Vector(-1.0, 1.0, -1.0),
                Vector(-1.0, -1.0, -1.0),

                Vector(-1.0, 1.0, 1.0),
                Vector(-1.0, -1.0, -1.0),
                Vector(-1.0, 1.0, -1.0),
                Vector(-1.0, 1.0, 1.0),
                Vector(-1.0, -1.0, 1.0),
                Vector(-1.0, -1.0, -1.0),

                Vector(1.0, 1.0, 1.0),
                Vector(1.0, -1.0, -1.0),
                Vector(1.0, 1.0, -1.0),
                Vector(1.0, 1.0, 1.0),
                Vector(1.0, -1.0, 1.0),
                Vector(1.0, -1.0, -1.0),

                Vector(1.0, 1.0, 1.0),
                Vector(-1.0, 1.0, -1.0),
                Vector(1.0, 1.0, -1.0),
                Vector(1.0, 1.0, 1.0),
                Vector(-1.0, 1.0, 1.0),
                Vector(-1.0, 1.0, -1.0),

                Vector(1.0, 1.0, 1.0),
                Vector(-1.0, -1.0, 1.0),
                Vector(1.0, -1.0, 1.0),
                Vector(1.0, 1.0, 1.0),
                Vector(-1.0, 1.0, 1.0),
                Vector(-1.0, -1.0, 1.0)};
    }

    static vector<Vector> getCubeNormals() {
        return {Vector(0.0, -1.0, 0.0),
                Vector(0.0, -1.0, 0.0),
                Vector(0.0, -1.0, 0.0),
                Vector(0.0, -1.0, 0.0),
                Vector(0.0, -1.0, 0.0),
                Vector(0.0, -1.0, 0.0),

                Vector(0.0, 0.0, -1.0),
                Vector(0.0, 0.0, -1.0),
                Vector(0.0, 0.0, -1.0),
                Vector(0.0, 0.0, -1.0),
                Vector(0.0, 0.0, -1.0),
                Vector(0.0, 0.0, -1.0),

                Vector(-1.0, 0.0, 0.0),
                Vector(-1.0, 0.0, 0.0),
                Vector(-1.0, 0.0, 0.0),
                Vector(-1.0, 0.0, 0.0),
                Vector(-1.0, 0.0, 0.0),
                Vector(-1.0, 0.0, 0.0),

                Vector(1.0, 0.0, 0.0),
                Vector(1.0, 0.0, 0.0),
                Vector(1.0, 0.0, 0.0),
                Vector(1.0, 0.0, 0.0),
                Vector(1.0, 0.0, 0.0),
                Vector(1.0, 0.0, 0.0),

                Vector(0.0, 1.0, 0.0),
                Vector(0.0, 1.0, 0.0),
                Vector(0.0, 1.0, 0.0),
                Vector(0.0, 1.0, 0.0),
                Vector(0.0, 1.0, 0.0),
                Vector(0.0, 1.0, 0.0),

                Vector(0.0, 0.0, 1.0),
                Vector(0.0, 0.0, 1.0),
                Vector(0.0, 0.0, 1.0),
                Vector(0.0, 0.0, 1.0),
                Vector(0.0, 0.0, 1.0),
                Vector(0.0, 0.0, 1.0)};
    };
};

#endif //BILLIARDS_GEOMETRICOBJECTS_H
