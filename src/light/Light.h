#ifndef BILLIARDS_LIGHT_H
#define BILLIARDS_LIGHT_H

#include "Vector.h"

class Light {
public:
    Vector position;
    Vector ambientColor;
    Vector diffuseColor;
    Vector specularColor;

    Light(Vector position, Vector ambientColor, Vector diffuseColor, Vector specularColor);
};

#endif //BILLIARDS_LIGHT_H
