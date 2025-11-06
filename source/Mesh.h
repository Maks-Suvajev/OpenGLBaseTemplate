#ifndef MESH_H
#define MESH_H

#include "glad.h"
#include <vector>
#include "Shader.h"

namespace gfx
{

struct Material
{
    std::unique_ptr<Shader> shader;
    GLuint texture;
};

struct MeshData
{   
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    Material material;
};

class Mesh
{


    Mesh(MeshData initData);








    private:
        GLuint VAO;
        GLuint VBO;
        GLuint EBO;













};

}

#endif