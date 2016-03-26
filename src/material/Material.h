#ifndef BILLIARDS_MATERIAL_H
#define BILLIARDS_MATERIAL_H

#include "Texture.h"
#include "Shader.h"

class Material {
    private:
        Shader *shader;
        Texture *texture;
    public:
        Material(Shader *shader);

        Shader *getShader();

        void setTexture(Texture *texture);

        Texture *getTexture();
};

#endif 
