#include "ResourceManager.h"

Shader ResourceManager::boundingObjectShader;
Shader ResourceManager::tableModelShader;
unordered_map<string, Texture> ResourceManager::textures;

void ResourceManager::installResources() {
    ResourceManager::boundingObjectShader = Shader("resources/shaders/bounding_object_vert.glsl",
                                                   "resources/shaders/bounding_object_frag.glsl");
    ResourceManager::tableModelShader = Shader("resources/shaders/vert.glsl",
                                               "resources/shaders/frag.glsl");
    textures["black.jpg"] = Texture("black.jpg");
    textures["chrome.jpg"] = Texture("chrome.jpg");
    textures["felt.jpg"] = Texture("felt.jpg");
    textures["mahogany.jpg"] = Texture("mahogany.jpg");
}

Texture &ResourceManager::getTexture(string name) {
    if (textures.count(name) == 0) {
        Util::log(Severity::WARNING, "Loading texture WHILE program is running: " + name);
        textures[name] = Texture(name);
    }
    return textures[name];
}
