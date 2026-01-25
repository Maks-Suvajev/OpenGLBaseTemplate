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
};

struct GpuHandles
{
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;
    bool useEBO;
};

struct MeshEntry
{
    std::string name;
    MeshData meshData;
};




}


#endif