#ifndef BILLIARDS_MATERIAL_H
#define BILLIARDS_MATERIAL_H

#include "Vector.h"
#include "Texture.h"

class Material {
public:
    Vector ambientColor;
    Vector diffuseColor;
    Vector specularColor;
    Texture *texture;
    float shininess;

    Material(Texture *texture, Vector ambientColor, Vector diffuseColor, Vector specularColor, float shininess);
};

#endif //BILLIARDS_MATERIAL_H
