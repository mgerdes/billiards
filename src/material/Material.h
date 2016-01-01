#ifndef BILLIARDS_MATERIAL_H
#define BILLIARDS_MATERIAL_H

#include "Vector.h"

class Material {
public:
    Vector ambientColor;
    Vector diffuseColor;
    Vector specularColor;
    float shininess;

    Material(Vector ambientColor, Vector diffuseColor, Vector specularColor, float shininess);
};

#endif //BILLIARDS_MATERIAL_H
