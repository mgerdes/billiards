#include "ResourceManager.h"

ResourceManager::ResourceManager() : boundingObjectShader("resources/shaders/vert.glsl", "resources/shaders/frag.glsl"),
                                     boundingObjectMaterial(Vector(1, 1, 1), Vector(1, 1, 1), Vector(1, 1, 1), 1.0),
                                     tableModelShader("resources/shaders/vert.glsl", "resources/shaders/frag.glsl") { }
