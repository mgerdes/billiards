#ifndef BILLIARDS_TEXTURE_H
#define BILLIARDS_TEXTURE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Util.h"

class Texture {
    private:
        unsigned int location;
    public:
        Texture();

        Texture(const char *fileName);

        void bind();

        void unbind();
};

#endif
