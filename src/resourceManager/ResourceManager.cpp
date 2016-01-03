#include "ResourceManager.h"

Shader ResourceManager::boundingObjectShader;
Shader ResourceManager::tableModelShader;

void ResourceManager::installResources() {
    ResourceManager::boundingObjectShader = Shader("resources/shaders/bounding_object_vert.glsl",
                                                   "resources/shaders/bounding_object_frag.glsl");
    ResourceManager::tableModelShader = Shader("resources/shaders/vert.glsl", "resources/shaders/frag.glsl");
}

