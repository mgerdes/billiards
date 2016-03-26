#include "ResourceManager.h"

std::unordered_map<std::string, Shader*> ResourceManager::shaders;
std::unordered_map<std::string, Texture*> ResourceManager::textures;

void ResourceManager::installTextures() {
    textures["resources/textures/mahogany.jpg"] = new Texture("resources/textures/mahogany.jpg");
    textures["resources/textures/black.jpg"] = new Texture("resources/textures/black.jpg");
    textures["resources/textures/felt.jpg"] = new Texture("resources/textures/felt.jpg");
    textures["resources/textures/cue.png"] = new Texture("resources/textures/cue.png");
    textures["resources/textures/chrome.jpg"] = new Texture("resources/textures/chrome.jpg");
    textures["resources/textures/0.png"] = new Texture("resources/textures/0.png");
    textures["resources/textures/1.png"] = new Texture("resources/textures/1.png");
    textures["resources/textures/2.png"] = new Texture("resources/textures/2.png");
    textures["resources/textures/3.png"] = new Texture("resources/textures/3.png");
    textures["resources/textures/4.png"] = new Texture("resources/textures/4.png");
    textures["resources/textures/5.png"] = new Texture("resources/textures/5.png");
    textures["resources/textures/6.png"] = new Texture("resources/textures/6.png");
    textures["resources/textures/7.png"] = new Texture("resources/textures/7.png");
    textures["resources/textures/8.png"] = new Texture("resources/textures/8.png");
    textures["resources/textures/9.png"] = new Texture("resources/textures/9.png");
    textures["resources/textures/10.png"] = new Texture("resources/textures/10.png");
    textures["resources/textures/11.png"] = new Texture("resources/textures/11.png");
    textures["resources/textures/12.png"] = new Texture("resources/textures/12.png");
    textures["resources/textures/13.png"] = new Texture("resources/textures/13.png");
    textures["resources/textures/14.png"] = new Texture("resources/textures/14.png");
    textures["resources/textures/15.png"] = new Texture("resources/textures/15.png");
}

void ResourceManager::installShaders() {
    Shader *s1 = new Shader("resources/shaders/basic_vert.glsl",
            "resources/shaders/basic_frag.glsl");
    s1->addProperty("proj_mat");
    s1->addProperty("view_mat");
    shaders["basic"] = s1;

    Shader *s2 = new Shader("resources/shaders/basic_texture_vert.glsl",
            "resources/shaders/basic_texture_frag.glsl");
    s2->addProperty("proj_mat");
    s2->addProperty("view_mat");
    shaders["basic_texture"] = s2;
}

void ResourceManager::installResources() {
    installShaders();
    installTextures();
}

Shader *ResourceManager::getShader(const char *name) {
    return shaders[name];
}

Texture *ResourceManager::getTexture(const char *name) {
    return textures[name];
}
