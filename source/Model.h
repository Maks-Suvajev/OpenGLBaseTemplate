#ifndef MODEL_H
#define MODEL_H

#include "Mesh.h"
#include <glm/glm.hpp>
#include <vector>
#include <memory>


namespace gfx
{



struct Part
{
    Material* material;
    Mesh* mesh;
};

struct MaterialMeshPair
{
    Material material;
    MeshData meshData;
};


struct ModelInitData
{
    Transform* transform;
    std::vector<MaterialMeshPair> materialMeshPairs;
};



class Model
{
    public:
        Model(ModelInitData initData);

        void drawModel();

        std::vector<Material*> getMaterials();


    private:
        void reconstructModelMatrix();
};

}

#endif