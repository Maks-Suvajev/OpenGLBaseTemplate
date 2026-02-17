#ifndef LIGHT_TYPES_H
#define LIGHT_TYPES_H

#include <glm/glm.hpp>

namespace gfx
{

// Constituent structs
struct LightColours
{
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

struct PointLightConstants
{
    float constant;
    float linear;
    float quadratic;
};

struct CutOff
{
    float outer;
    float inner;
};


// Light component structs
struct SpotLight
{
    LightColours lightColours;
    glm::vec3 position;
    glm::vec3 direction;
    CutOff cutOff;
};

struct PointLight
{
    LightColours lightColours;
    glm::vec3 position;
    PointLightConstants constants;
    int shaderIndex;
};

struct DirectionalLight
{
    LightColours lightColours;
    glm::vec3 direction;
};


}
#endif