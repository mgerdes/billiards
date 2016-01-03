#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(string file) {
    string fileName = "resources/textures/" + file;
    int x, y, n;
    int force_channels = 3;
    unsigned char* image_data = stbi_load(fileName.c_str(), &x, &y, &n, force_channels);
    if (!image_data) {
        Util::log(Severity::ERROR , "Could not load texture image file: " + fileName);
        return;
    }

    glGenTextures(1, &location);
    glBindTexture(GL_TEXTURE_2D, location);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, image_data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    free(image_data);
}

Texture::Texture() : location(0) { }

void Texture::enable() {
    glBindTexture(GL_TEXTURE_2D, location);
}

void Texture::disable() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

