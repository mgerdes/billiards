#ifndef BILLIARDS_RESOURCEMANAGER_H
#define BILLIARDS_RESOURCEMANAGER_H

#include "Shader.h"
#include "Material.h"
#include "BoundingObject.h"

class ResourceManager {
public:
    static Shader boundingObjectShader;
    static Material boundingObjectMaterial;
    static Shader tableModelShader;

    static void installResources();
};

#endif //BILLIARDS_RESOURCEMANAGER_H
