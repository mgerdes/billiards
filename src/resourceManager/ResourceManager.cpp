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
    textures["0.png"] = Texture("0.png");
    textures["1.png"] = Texture("1.png");
    textures["2.png"] = Texture("2.png");
    textures["3.png"] = Texture("3.png");
    textures["4.png"] = Texture("4.png");
    textures["5.png"] = Texture("5.png");
    textures["6.png"] = Texture("6.png");
    textures["7.png"] = Texture("7.png");
    textures["8.png"] = Texture("8.png");
    textures["9.png"] = Texture("9.png");
    textures["10.png"] = Texture("10.png");
    textures["11.png"] = Texture("11.png");
    textures["12.png"] = Texture("12.png");
    textures["13.png"] = Texture("13.png");
    textures["14.png"] = Texture("14.png");
    textures["15.png"] = Texture("15.png");
}

Texture &ResourceManager::getTexture(string name) {
    if (textures.count(name) == 0) {
        Util::log(Severity::WARNING, "Loading texture WHILE program is running: " + name);
        textures[name] = Texture(name);
    }
    return textures[name];
}
