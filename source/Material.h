#ifndef MATERIAL_H
#define MATERIAL_H

#include "glad/glad.h"
#include <utility>

namespace gfx
{

struct LightingTextures
{
    GLuint diffuse;
    GLuint specular;
};

// Component
struct MaterialProperties
{
    GLuint shader; // Shader used for the material
    LightingTextures lightingTextures;
    float shininess;
    bool isLightSource;
};


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