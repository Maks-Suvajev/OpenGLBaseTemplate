#ifndef MATERIAL_TYPES_H
#define MATERIAL_TYPES_H

#include "glad.h"

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
};

}
#endif