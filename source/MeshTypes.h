#ifndef MESH_TYPES_H
#define MESH_TYPES_H

#include "glad/glad.h"
#include <vector>
#include <string>

namespace gfx
{

struct MeshData
{   
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    uint32_t numVertices;
};

// Component structure
struct GpuHandles
{
    GLuint   VAO;
    GLuint   VBO;
    GLuint   EBO;
    bool     useEBO;
    uint32_t numVertices;
};

// Init structure
struct MeshEntry
{
    std::string name;
    MeshData meshData;
};


}


#endif