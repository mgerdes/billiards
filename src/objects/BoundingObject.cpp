#include "BoundingObject.h"

vector<Vector> RectangleBoundingObject::rectangleVertices = {Vector(-0.5f, 0, -0.5f),
                                                             Vector(-0.5f, 0, 0.5f),
                                                             Vector(0.5f, 0, 0.5f),
                                                             Vector(0.5f, 0, -0.5f)};

vector<Vector> RectangleBoundingObject::rectangleNormals = {Vector(0, 1, 0),
                                                            Vector(0, 1, 0),
                                                            Vector(0, 1, 0),
                                                            Vector(0, 1, 0)};

RectangleBoundingObject::RectangleBoundingObject(float x, float y, float width, float height)
        : x{x},
          y{y},
          width{width},
          height{height},
          mesh(RectangleBoundingObject::rectangleVertices,
               RectangleBoundingObject::rectangleNormals,
               ResourceManager::boundingObjectShader,
               MeshType::LINE_LOOP) { }

void RectangleBoundingObject::draw() {
    Matrix translation = Matrix(Vector(x, 0.0f, y));
    Matrix scale = Matrix::scaleMatrix(Vector(width, 1.0f, height));
    Matrix modelMat = translation * scale;
    mesh.shader.setMatProperty("model_mat", modelMat.m);
    mesh.draw();
}

vector<Vector> CircleBoundingObject::circleVertices = createCircleVertices();

vector<Vector> CircleBoundingObject::circleNormals = createCircleNormals();

CircleBoundingObject::CircleBoundingObject(float x, float y, float radius)
        : x{x},
          y{y},
          radius{radius},
          mesh(CircleBoundingObject::circleVertices,
               CircleBoundingObject::circleNormals,
               ResourceManager::boundingObjectShader,
               MeshType::LINE_LOOP) { }

void CircleBoundingObject::draw() {
    Matrix translation = Matrix(Vector(x, 0.0, y));
    Matrix scale = Matrix(radius);
    Matrix modelMat = translation * scale;
    mesh.shader.setMatProperty("model_mat", modelMat.m);
    mesh.draw();
}

vector<Vector> CircleBoundingObject::createCircleVertices() {
    vector<Vector> vertices;

    float theta = 0;
    float delta = (float) (2.0 * M_PI / NUM_POINTS);

    for (int i = 0; i < NUM_POINTS; i++) {
        float circleX = cos(theta);
        float circleY = sin(theta);
        vertices.push_back(Vector(circleX, 0, circleY));
        theta += delta;
    }

    return vertices;
}

vector<Vector> CircleBoundingObject::createCircleNormals() {
    vector<Vector> vertices;

    for (int i = 0; i < NUM_POINTS; i++) {
        vertices.push_back(Vector(0, 1, 0));
    }

    return vertices;
}
