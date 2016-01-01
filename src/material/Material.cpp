#include "Material.h"

Material::Material(Vector ambientColor,
                   Vector diffuseColor,
                   Vector specularColor,
                   float shininess) : ambientColor(ambientColor),
                                      diffuseColor(diffuseColor),
                                      specularColor(specularColor),
                                      shininess(shininess) { }
