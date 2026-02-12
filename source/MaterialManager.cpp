#include "MaterialManager.h"

namespace gfx
{

void MaterialManager::addMaterial(std::string name, MaterialProperties&& materialInitProperties)
{
    if (!materials.contains(name))
    {
        materials[name] = std::make_unique<Material>(std::move(materialInitProperties));
    }
    else
    {
        #ifdef ENABLE_DEBUG_MESSAGES
            std::cout << "ERROR::Material name already exists - try different key - doing nothing." << std::endl;
        #endif
    }
}

Material* MaterialManager::getMaterial(std::string materialName)
{
    if (materials.contains(materialName))
    {
        return materials[materialName].get();
    }

    #ifdef ENABLE_DEBUG_MESSAGES
        std::cout << "ERROR::Requested material name does not exist: " << materialName << std::endl;
    #endif

    return nullptr;
}

}