#include "Material.h"

namespace gfx
{

Material::Material(MaterialProperties&& materialInitProperties)
    : materialProperties(std::move(materialInitProperties))
{
}





}