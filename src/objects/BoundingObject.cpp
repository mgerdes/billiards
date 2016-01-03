#include "BoundingObject.h"

RectangleBoundingObject::RectangleBoundingObject(float x, float y, float width, float height)
        : x{x},
          y{y},
          width{width},
          height{height},
          mesh(RectangleBoundingObject::getRectangleVertices(x, y, width, height),
               RectangleBoundingObject::getRectangleNormals(),
               ResourceManager::boundingObjectShader,
               MeshType::LINE_LOOP) { }

void RectangleBoundingObject::draw() {
    mesh.draw();
}

vector<Vector> RectangleBoundingObject::getRectangleVertices(float x, float y, float width, float height) {
    return {Vector(x, 0, y),
            Vector(x, 0, y + height),
            Vector(x + width, 0, y + height),
            Vector(x + width, 0, y)};
}

vector<Vector> RectangleBoundingObject::getRectangleNormals() {
    return {Vector(0, 1, 0),
            Vector(0, 1, 0),
            Vector(0, 1, 0),
            Vector(0, 1, 0)};
}

CircleBoundingObject::CircleBoundingObject(float x, float y, float radius)
        : x{x},
          y{y},
          radius{radius},
          mesh(CircleBoundingObject::getCircleVertices(x, y, radius),
               CircleBoundingObject::getCircleNormals(),
               ResourceManager::boundingObjectShader,
               MeshType::LINE_LOOP) { }

void CircleBoundingObject::draw() {
    mesh.draw();
}

vector<Vector> CircleBoundingObject::getCircleVertices(float x, float y, float radius) {
    vector<Vector> vertices;

    float theta = 0;
    float delta = (float) (2.0 * M_PI / NUM_POINTS);

    for (int i = 0; i < NUM_POINTS; i++) {
        float circle_x = radius * cos(theta) + x;
        float circle_y = radius * sin(theta) + y;
        vertices.push_back(Vector(circle_x, 0, circle_y));
        theta += delta;
    }

    return vertices;
}

vector<Vector> CircleBoundingObject::getCircleNormals() {
    vector<Vector> vertices;

    for (int i = 0; i < NUM_POINTS; i++) {
        vertices.push_back(Vector(0, 1, 0));
    }

    return vertices;
}
