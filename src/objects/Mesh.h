#ifndef BILLIARDS_MESH_H
#define BILLIARDS_MESH_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "Vector.h"
#include "Shader.h"
#include "Material.h"

using namespace std;

enum MeshType { LINE_LOOP = GL_LINE_LOOP, TRIANGLE = GL_TRIANGLES };

class Mesh {
private:
    MeshType type;
    GLuint vao;
    int numberOfVertices;
public:
    Material material;
    Shader &shader;

    Mesh(vector<Vector> verticesVector,
         vector<Vector> normalsVector,
         vector<Vector> textureCoordinatesVector,
         Material material,
         Shader &shader,
         MeshType type = MeshType::TRIANGLE);

    Mesh(vector<Vector> verticesVector,
         vector<Vector> normalsVector,
         Material material,
         Shader &shader,
         MeshType type = MeshType::TRIANGLE);

    void draw();
};

#endif //BILLIARDS_MESH_H
