#include "Renderer.h"

namespace gfx
{
    void Renderer::bindVAO(GLuint VAO)
    {
        glBindVertexArray(VAO);
    }

    void Renderer::draw(uint32_t numVertices, bool EBO)
    {
        if (EBO)
        { 
            glDrawElements(GL_TRIANGLES, numVertices, GL_UNSIGNED_INT, 0);
        }
        else
        {
            glDrawArrays(GL_TRIANGLES, 0, numVertices);
        }
    }

    void Renderer::applyMaterial(gfx::MaterialProperties* material, Shader* shader)
    {
        //TODO: uniform names shouldnt be hardcoded here.
        shader->updateUniformValue("material.shininess", material->shininess);

        shader->updateUniformValue("material.diffuse", 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, material->lightingTextures.diffuse);

        shader->updateUniformValue("material.specular", 1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, material->lightingTextures.specular);
    }

    void Renderer::render(glm::mat4& modelMatrix, GpuHandles* gpuHandle, gfx::MaterialProperties* material, Shader* shader)
    {
        shader->useProgram();
        shader->updateModelMatrixValue(modelMatrix);

        applyMaterial(material, shader);

        bindVAO(gpuHandle->VAO);
        draw(gpuHandle->numVertices, gpuHandle->useEBO);
    }
}