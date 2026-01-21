#ifndef MESH_H
#define MESH_H

#include "glad.h"
#include <vector>
#include "Shader.h"

namespace gfx
{

struct MeshData
{   
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
};

class Mesh
{
    public:
        Mesh(MeshData initData);
        void drawMesh();
        void bindVAO();

};








}

#endif