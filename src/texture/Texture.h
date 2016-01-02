#ifndef BILLIARDS_TEXTURE_H
#define BILLIARDS_TEXTURE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include "Util.h"

class Texture {
private:
    GLuint location;
public:
    Texture();

    Texture(string fileName);

    void enable();

    void disable();
};

#endif //BILLIARDS_TEXTURE_H
