#ifndef BILLIARDS_MESH_H
#define BILLIARDS_MESH_H

#include "Object3D.h"
#include "Geometry.h"
#include "Material.h"

class Mesh : public Object3D {
    private:
        unsigned int VAO;

        Geometry *geometry;
        Material *material;
    public:
        Mesh(Geometry *geometry, Material *material);

        void draw();

        Material *getMaterial();
};

#endif 
