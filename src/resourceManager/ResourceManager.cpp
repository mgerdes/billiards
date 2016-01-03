#include "ResourceManager.h"

Shader ResourceManager::boundingObjectShader;
Material ResourceManager::boundingObjectMaterial;
Shader ResourceManager::tableModelShader;

void ResourceManager::installResources() {
    ResourceManager::boundingObjectShader = Shader("resources/shaders/vert.glsl", "resources/shaders/frag.glsl");
    ResourceManager::boundingObjectMaterial = Material(Vector(1, 1, 1), Vector(1, 1, 1), Vector(1, 1, 1), 1.0);
    ResourceManager::tableModelShader = Shader("resources/shaders/vert.glsl", "resources/shaders/frag.glsl");
}

