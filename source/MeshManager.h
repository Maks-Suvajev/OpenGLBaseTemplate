#ifndef MESH_MANAGER_H
#define MESH_MANAGER_H

#include <unordered_map>
#include <string>
#include "Mesh.h"

namespace gfx
{

struct MeshEntry
{
    std::string name;
    MeshData meshData;
};

class MeshManager
{
    public:
        MeshManager() = default;
        MeshManager(std::vector<MeshEntry>&& meshList);
        //TODO: Next thought - should i take in a vector for initing also? be all polymorphic?
        void addMesh(std::string meshName, MeshData&& meshData);


    private:
        std::unordered_map<std::string, std::unique_ptr<Mesh>> meshes;

};

}

#endif