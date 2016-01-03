#ifndef BILLIARDS_RESOURCEMANAGER_H
#define BILLIARDS_RESOURCEMANAGER_H

#include "Shader.h"
#include "Material.h"
#include "BoundingObject.h"

class ResourceManager {
public:
    static Shader boundingObjectShader;
    static Shader tableModelShader;
    static unordered_map<string, Texture> textures;

    static void installResources();

    static Texture &getTexture(string name);
};

#endif //BILLIARDS_RESOURCEMANAGER_H
