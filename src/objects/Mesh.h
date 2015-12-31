#ifndef BILLIARDS_MESH_H
#define BILLIARDS_MESH_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "Vec.h"
#include "Shader.h"

using namespace std;

class Mesh {
private:
    GLuint vao;
    int numberOfVertices;
    const Shader &shader;
public:
    Mesh(vector<Vec> vertices, const Shader &shader);

    void draw();
};

#endif //BILLIARDS_MESH_H
