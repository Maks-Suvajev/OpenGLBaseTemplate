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
}