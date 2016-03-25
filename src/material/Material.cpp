#include "Material.h"

Material::Material(Shader *shader) {
    this->shader = shader;
}

Shader *Material::getShader() {
    return shader;
}
