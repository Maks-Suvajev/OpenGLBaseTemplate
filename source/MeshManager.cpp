#include "Meshmanager.h"

namespace gfx
{
    void MeshManager::addMesh(std::string meshName, MeshData&& meshData)
    {
        meshes[meshName] = std::make_unique<Mesh>(std::move(meshData));
    }

    MeshManager::MeshManager(std::vector<MeshEntry>&& meshList)
    {
        for (auto& meshEntry : meshList)
        {
            addMesh(std::move(meshEntry.name), std::move(meshEntry.meshData));
        }

        printAllMeshNames();
    }

    void MeshManager::printAllMeshNames()
    {
        uint32_t total_meshes = 0;

        std::cout << "-----------------------------------" << std::endl;
        std::cout << "Meshes currently loaded:           " << std::endl;
        std::cout << "-----------------------------------" << std::endl;

        for (auto& [key, mesh] : meshes)
        {
            std::cout << "Mesh name: " << key << std::endl;

            ++total_meshes;
        }

        std::cout << "-----------------------------------" << std::endl;

        std::cout << "There are a total of " << total_meshes << " meshes." << std::endl;
    }


}