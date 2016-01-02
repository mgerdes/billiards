#ifndef BILLIARDS_MESH_H
#define BILLIARDS_MESH_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "Vector.h"
#include "Shader.h"
#include "Material.h"

using namespace std;

class Mesh {
private:
    GLuint vao;
    int numberOfVertices;
public:
    Material material;
    Shader &shader;

    Mesh(vector<Vector> verticesVector,
         vector<Vector> normalsVector,
         vector<Vector> textureCoordinatesVector,
         Material material,
         Shader &shader);

    Mesh(vector<Vector> verticesVector,
         vector<Vector> normalsVector,
         Material material,
         Shader &shader);

    void draw();
};

#endif //BILLIARDS_MESH_H
