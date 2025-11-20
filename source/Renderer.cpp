#include "Renderer.h"

namespace gfx
{
    Renderer::Renderer(std::vector<ModelInitData> modelsToInit)
    {
        for (auto& modelToInit : modelsToInit)
        {
            std::unique_ptr<Model> newModelInstance = std::make_unique<Model>(modelToInit);
            models.push_back(std::move(newModelInstance));
        }
    }

    void Renderer::updateViewPosForSpecularLight(glm::vec3 cameraPos)
    {
        for (const auto& model : models)
        {   
            std::vector<Material*> materials = model->getMaterials();

            for (const auto& material : materials)
            {

                if (!material->isLightSource)
                {
                    material->shader->updateUniformValue("viewPos", cameraPos);
                }
            }
        }
    }
}