#ifndef COMPONENT_TYPES_H
#define COMPONENT_TYPES_H

#include <glm/glm.hpp>

// Component
struct Transform
{
    glm::vec3 position;
    glm::vec3 rotation; //Euler rotation
    glm::vec3 scaleFactors;
    glm::mat4 modelMatrix;
};

struct MaterialProperties
{
    GLuint diffuse;
    GLuint specular;
    float shininess; 
};

// Component
struct Material
{
    GLuint shader;
    MaterialProperties materialProp;
    bool isLightSource;
};

// Component
struct MeshGPUData
{
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;
};


#endif