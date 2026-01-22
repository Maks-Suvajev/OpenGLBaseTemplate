#include "Meshmanager.h"

namespace gfx
{
    void MeshManager::addMesh(std::string meshName, MeshData&& meshData)
    {
        meshes[meshName] = std::make_unique<Mesh>(std::move(meshData));

    }

}