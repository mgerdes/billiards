#include "Material.h"

Material::Material(Shader *shader) {
    this->shader = shader;
}

Shader *Material::getShader() {
    return shader;
}

void Material::setTexture(Texture *texture) {
    this->texture = texture;
}

Texture *Material::getTexture() {
    return texture;
}
