#include "ResourceManager.h"

unordered_map<string, Texture *> ResourceManager::textures;
unordered_map<string, Shader *> ResourceManager::shaders;
unordered_map<string, Model *> ResourceManager::models;

void ResourceManager::installResources() {
    textures["black.jpg"] = new Texture("black.jpg");
    textures["chrome.jpg"] = new Texture("chrome.jpg");
    textures["felt.jpg"] = new Texture("felt.jpg");
    textures["mahogany.jpg"] = new Texture("mahogany.jpg");
    textures["0.png"] = new Texture("0.png");
    textures["1.png"] = new Texture("1.png");
    textures["2.png"] = new Texture("2.png");
    textures["3.png"] = new Texture("3.png");
    textures["4.png"] = new Texture("4.png");
    textures["5.png"] = new Texture("5.png");
    textures["6.png"] = new Texture("6.png");
    textures["7.png"] = new Texture("7.png");
    textures["8.png"] = new Texture("8.png");
    textures["9.png"] = new Texture("9.png");
    textures["10.png"] = new Texture("10.png");
    textures["11.png"] = new Texture("11.png");
    textures["12.png"] = new Texture("12.png");
    textures["13.png"] = new Texture("13.png");
    textures["14.png"] = new Texture("14.png");
    textures["15.png"] = new Texture("15.png");
    textures["cue.png"] = new Texture("cue.png");

    shaders["bounding_object"] = new Shader("resources/shaders/bounding_object_vert.glsl",
                                            "resources/shaders/bounding_object_frag.glsl");
    shaders["default"] = new Shader("resources/shaders/vert.glsl", "resources/shaders/frag.glsl");

    models["billiards_stick"] = new Model("resources/models/cue.obj");
    models["billiards_table"] = new Model("resources/models/table.obj");
    models["billiards_ball"] = new Model("resources/models/ball.obj");
}

Texture *ResourceManager::getTexture(string name) {
    if (textures.count(name) == 0) {
        Util::log(Severity::WARNING, "Loading texture WHILE program is running: " + name);
        textures[name] = new Texture(name);
    }
    return textures[name];
}

Shader *ResourceManager::getShader(string name) {
    if (shaders.count(name) == 0) {
        Util::log(Severity::ERROR, "Could not find shader: " + name);
        return 0;
    }
    return shaders[name];
}

Model *ResourceManager::getModel(string name) {
    if (models.count(name) == 0) {
        Util::log(Severity::ERROR, "Could not find model: " + name);
        return 0;
    }
    return models[name];
}
