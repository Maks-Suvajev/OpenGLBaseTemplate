#include "Renderer.h"

namespace gfx
{
    // void Renderer::updateViewPosForSpecularLight(glm::vec3 cameraPos)
    // {
    //     for (const auto& model : models)
    //     {   
    //         std::vector<Material*> materials = model->getMaterials();

    //         for (const auto& material : materials)
    //         {

    //             if (!material->isLightSource)
    //             {
    //                 material->shader->updateUniformValue("viewPos", cameraPos);
    //             }
    //         }
    //     }
    // }


    void Renderer::bindVAO(GLuint VAO)
    {
        glBindVertexArray(VAO);
    }

    void Renderer::draw(bool EBO)
    {
        if (EBO)
        { //TODO: Fix hardcoded vertex count
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        }
        else
        {
            glDrawArrays(GL_TRIANGLES, 0, 36);
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

    void Renderer::applyLighting(Shader* shader)
    {
        //TODO: For light renderer:
        glm::vec3 lightColor{1.0f};
        glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
        glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);
        // ---------

        shader->updateUniformValue("spotLight.ambient",   ambientColor);
        shader->updateUniformValue("spotLight.diffuse",   diffuseColor);
        shader->updateUniformValue("spotLight.specular",  lightColor);

        shader->updateUniformValue("pointLights[0].ambient",   ambientColor);
        shader->updateUniformValue("pointLights[0].diffuse",   diffuseColor);
        shader->updateUniformValue("pointLights[0].specular",  lightColor);
        shader->updateUniformValue("pointLights[0].position",  glm::vec3(1.2f, 1.0, 2.0f));

        shader->updateUniformValue("pointLights[0].constant",  1.0f);
        shader->updateUniformValue("pointLights[0].linear",  0.09f);
        shader->updateUniformValue("pointLights[0].quadratic",  0.032f);

        shader->updateUniformValue("directionalLight.direction",   glm::vec3(-0.2f, -1.0f, -0.3f));
        shader->updateUniformValue("directionalLight.ambient",   ambientColor);
        shader->updateUniformValue("directionalLight.diffuse",   diffuseColor);
        shader->updateUniformValue("directionalLight.specular",  lightColor);
    }

    void Renderer::render(glm::mat4& modelMatrix, GpuHandles* gpuHandle, gfx::MaterialProperties* material, Shader* shader)
    {
        shader->useProgram();
        shader->updateModelMatrixValue(modelMatrix);

        applyMaterial(material, shader);
        applyLighting(shader);

        bindVAO(gpuHandle->VAO);
        draw(gpuHandle->useEBO);
    }
}