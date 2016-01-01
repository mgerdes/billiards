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
    Material material;
    Shader &shader;
public:
    Mesh(vector<Vector> vertices, vector<Vector> normals, Material material, Shader &shader);

    void draw();
};

#endif //BILLIARDS_MESH_H
