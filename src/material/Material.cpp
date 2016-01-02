#include "Material.h"

Material::Material(Vector ambientColor,
                   Vector diffuseColor,
                   Vector specularColor,
                   float shininess) : ambientColor(ambientColor),
                                      diffuseColor(diffuseColor),
                                      specularColor(specularColor),
                                      shininess(shininess) { }

Material::Material(Texture texture,
                   Vector ambientColor,
                   Vector diffuseColor,
                   Vector specularColor,
                   float shininess) : texture(texture),
                                      ambientColor(ambientColor),
                                      diffuseColor(diffuseColor),
                                      specularColor(specularColor),
                                      shininess(shininess) { }
