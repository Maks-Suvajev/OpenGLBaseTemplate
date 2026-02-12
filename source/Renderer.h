#ifndef RENDERER_H
#define RENDERER_H

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

        // Specular calculations require camera position in order to make the calculation.
        //void updateViewPosForSpecularLight(glm::vec3 cameraPos);



    private:
        void applyMaterial(gfx::MaterialProperties* material, Shader* shader);
        void applyLighting(Shader* shader);
        void draw(uint32_t numVertices, bool EBO);
        void bindVAO(GLuint VAO);

















};


}

#endif