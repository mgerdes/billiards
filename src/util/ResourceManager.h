#ifndef BILLIARDS_RESOURCE_MANAGER_H
#define BILLIARDS_RESOURCE_MANAGER_H

#include "Shader.h"
#include "Material.h"
#include "Geometry.h"

enum Shaders {
    BASIC
};

enum Materials {

};

enum Geometries {

};

class ResourceManager {
    private:
        static Shader **shaders;
        static Material **materials;
        static Geometry **geometries;
    public:
        static void installResources();

        static Shader *getShader(enum Shaders shader);
};

#endif
