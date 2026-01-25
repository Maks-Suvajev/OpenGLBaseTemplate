#ifndef MESH_H
#define MESH_H

#include "Shader.h"
#include "MeshTypes.h"

namespace gfx
{

class Mesh
{
    public:
        Mesh(MeshData&& initData);
        //void drawMesh();
        //void bindVAO();

        GpuHandles getGPUHandles()
        {
            return gpuHandles;
        }


    private:
        GpuHandles gpuHandles;

};

}

#endif