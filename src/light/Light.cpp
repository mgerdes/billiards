#include "Light.h"

Light::Light(Vector position,
             Vector ambientColor,
             Vector diffuseColor,
             Vector specularColor) : position(position),
                                     ambientColor(ambientColor),
                                     diffuseColor(diffuseColor),
                                     specularColor(specularColor) { }
