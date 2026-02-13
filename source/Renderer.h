#ifndef RENDERER_H
#define RENDERER_H

// STL
#include <memory>

#include "MeshTypes.h"
#include "MaterialTypes.h"
#include "Shader.h"

namespace gfx
{

class Renderer
{

    public:
        Renderer() = default;

        void render(glm::mat4& modelMatrix, GpuHandles* gpuHandle, gfx::MaterialProperties* material, Shader* shader);

    private:
        void applyMaterial(gfx::MaterialProperties* material, Shader* shader);
        void draw(uint32_t numVertices, bool EBO);
        void bindVAO(GLuint VAO);
};


}

#endif