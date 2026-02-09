#include "RenderSystem.h"

namespace gfx
{

glm::mat4& RenderSystem::updateAndGetModelMatrix(std::vector<gfx::Transform>::iterator& transformIter)
{
    transformIter->modelMatrix = glm::mat4(1.0f);

    // Translate
    transformIter->modelMatrix = glm::translate(transformIter->modelMatrix, transformIter->position);

    // Rotate in the order X -> Y -> Z every time
    transformIter->modelMatrix = glm::rotate(transformIter->modelMatrix, glm::radians(transformIter->rotation.x), glm::vec3{1.0f, 0.0f, 0.0f}); // x rotation
    transformIter->modelMatrix = glm::rotate(transformIter->modelMatrix, glm::radians(transformIter->rotation.y), glm::vec3{0.0f, 1.0f, 0.0f}); // y rotation
    transformIter->modelMatrix = glm::rotate(transformIter->modelMatrix, glm::radians(transformIter->rotation.z), glm::vec3{0.0f, 0.0f, 1.0f}) ; // z rotation

    // Scale
    transformIter->modelMatrix = glm::scale(transformIter->modelMatrix, transformIter->scaleFactors);

    return transformIter->modelMatrix;
}

void RenderSystem::runRender(Window* window, Renderer* renderer, EntityManager* entityManager, ShaderManager* shaderManager)
{
    auto transformPool = entityManager->getComponentPool<gfx::Transform>();

    if(transformPool == nullptr)
    {
        #ifdef ENABLE_DEBUG_MESSAGES
            std::cout << "ERROR::RenderSystem::runRender::Transform pool doesn't exist. Nothing to render." << std::endl;
        #endif
        return;
    }

    std::vector<gfx::Transform>::iterator poolBegin = transformPool->begin();
    std::vector<gfx::Transform>::iterator poolEnd = transformPool->end();

    for (auto transformIter = poolBegin; transformIter != poolEnd; ++transformIter)
    {
        size_t index = std::distance(poolBegin, transformIter);
        Entity entity = transformPool->getEntityID(index);

        auto mesh = getPoolElement<gfx::GpuHandles>(entity, entityManager);

        if (mesh != nullptr)
        {
            // Set default mesh
        }

        auto material = getPoolElement<gfx::MaterialProperties>(entity, entityManager);

        if (material != nullptr)
        {
            // Set default material
        }

        Shader* shader = shaderManager->getShaderPtr(material->shader);

        if (material != nullptr)
        {
            // Set default shader
        }

        shader->updateViewMatrixValue(window->getCameraInstance()->calculateViewMatrix());
		shader->updateProjectionMatrixValue(window->getCameraInstance()->calculateProjectionMatrix());
        
        renderer->render(updateAndGetModelMatrix(transformIter), mesh, material, shader);
    }
}


}
