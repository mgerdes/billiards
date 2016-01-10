#include "Material.h"

Material::Material() { }

Material::Material(Vector ambientColor,
                   Vector diffuseColor,
                   Vector specularColor,
                   float shininess)
        : ambientColor(ambientColor),
          diffuseColor(diffuseColor),
          specularColor(specularColor),
          shininess(shininess),
          hasTexture(false) { }

Material::Material(Texture texture,
                   Vector ambientColor,
                   Vector diffuseColor,
                   Vector specularColor,
                   float shininess)
        : texture(texture),
          ambientColor(ambientColor),
          diffuseColor(diffuseColor),
          specularColor(specularColor),
          shininess(shininess),
          hasTexture(true) { }
