#ifndef BILLIARDS_RESOURCEMANAGER_H
#define BILLIARDS_RESOURCEMANAGER_H

#include "Model.h"
#include "Shader.h"
#include "Material.h"
#include "BoundingObject.h"

class Model;

class ResourceManager {
private:
    static unordered_map<string, Shader *> shaders;
    static unordered_map<string, Model *> models;
    static unordered_map<string, Texture *> textures;

public:
    static void installResources();

    static Texture *getTexture(string name);
    static Shader *getShader(string name);
    static Model *getModel(string name);
};

#endif //BILLIARDS_RESOURCEMANAGER_H
