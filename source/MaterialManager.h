#ifndef MATERIAL_MANAGER_H
#define MATERIAL_MANAGER_H

#include "Material.h"
#include <string>
#include <memory>
#include <unordered_map>

namespace gfx
{

class MaterialManager
{
    public:
        MaterialManager() = default;
        void addMaterial(std::string name, MaterialProperties&& materialInitProperties);

    private:
        std::unordered_map<std::string, std::unique_ptr<Material>> materials;
    


};

}

#endif