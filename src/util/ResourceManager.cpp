#include "ResourceManager.h"

Shader **ResourceManager::shaders;

void ResourceManager::installResources() {
    shaders = new Shader*[1];
    shaders[0] = new Shader("resources/shaders/basic_vert.glsl",
            "resources/shaders/basic_frag.glsl");
    shaders[0]->addProperty("proj_mat");
    shaders[0]->addProperty("view_mat");
}

Shader *ResourceManager::getShader(enum Shaders shader) {
    return shaders[shader];
}
