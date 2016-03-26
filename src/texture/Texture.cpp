#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const char *fileName) {
    int x, y, n;
    int force_channels = 3;
    unsigned char* image_data = stbi_load(fileName, &x, &y, &n, force_channels);
    if (!image_data) {
        Util::log(Severity::ERROR , "Could not load texture image file: " + std::string(fileName));
        return;
    }

    glGenTextures(1, &location);
    bind();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, image_data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    unbind();

    free(image_data);
}

void Texture::bind() {
    glBindTexture(GL_TEXTURE_2D, location);
}

void Texture::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

