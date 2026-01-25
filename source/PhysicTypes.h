#ifndef PHYSICS_TYPES_H
#define PHYSICS_TYPES_H

#include "glad.h"
#include <glm/glm.hpp>

// Component
struct Transform
{
    glm::vec3 position;
    glm::vec3 rotation; //Euler rotation
    glm::vec3 scaleFactors;
    glm::mat4 modelMatrix;
};


#endif