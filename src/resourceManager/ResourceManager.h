#ifndef BILLIARDS_RESOURCEMANAGER_H
#define BILLIARDS_RESOURCEMANAGER_H

#include "Shader.h"
#include "Material.h"

class ResourceManager {
public:
    Shader boundingObjectShader;
    Material boundingObjectMaterial;
    Shader tableModelShader;

    ResourceManager();
};

#endif //BILLIARDS_RESOURCEMANAGER_H
