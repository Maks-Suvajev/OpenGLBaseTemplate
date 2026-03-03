#ifndef MATERIAL_H
#define MATERIAL_H

#include <utility>

#include "MaterialTypes.h"

namespace gfx
{

class Material
{

    public:
        Material() = default;
        Material(MaterialProperties&& materialInitProperties);

        MaterialProperties getMaterialProperties(){
            return materialProperties;
        };

    private:
        MaterialProperties materialProperties;

};

}
#endif