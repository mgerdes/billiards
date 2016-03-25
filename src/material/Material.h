#ifndef BILLIARDS_MATERIAL_H
#define BILLIARDS_MATERIAL_H

#include "Texture.h"
#include "Shader.h"

class Material {
    private:
        Shader *shader;
    public:
        Material(Shader *shader);

        Shader *getShader();
};

#endif 
