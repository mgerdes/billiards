#ifndef BILLIARDS_RESOURCE_MANAGER_H
#define BILLIARDS_RESOURCE_MANAGER_H

#include "Shader.h"
#include "Material.h"
#include "Geometry.h"

class ResourceManager {
    private:
        static std::unordered_map<std::string, Shader*> shaders;
        static std::unordered_map<std::string, Texture*> textures;

        static void installShaders();

        static void installTextures();
    public:
        static void installResources();

        static Shader *getShader(const char* name);

        static Texture *getTexture(const char* name);
};

#endif
