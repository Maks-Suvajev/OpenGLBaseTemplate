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


    void Renderer::renderHandle(GpuHandles& handle)
    {
        bindVAO(handle.VAO);

        if (handle.useEBO)
        {
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        }
        else
        {
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
    }
}