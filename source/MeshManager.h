#ifndef MESH_MANAGER_H
#define MESH_MANAGER_H

#include <unordered_map>
#include <string>
#include <optional>

#include "Mesh.h"

namespace gfx
{

class MeshManager
{
    public:
        MeshManager() = default;
        MeshManager(std::vector<MeshEntry>&& meshList);
        void addMesh(std::string meshName, MeshData&& meshData);

        Mesh* getMesh(std::string meshName);

        void printAllMeshNames();

    private:
        std::unordered_map<std::string, std::unique_ptr<Mesh>> meshes;
};

}

#endif