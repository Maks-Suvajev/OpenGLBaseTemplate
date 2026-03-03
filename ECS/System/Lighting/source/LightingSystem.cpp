#include "LightingSystem.h"


namespace gfx
{

LightingSystem::LightingSystem()
: pointLightCount(0U)
{
}

void LightingSystem::addSpotLight(EntityManager* entityManager, Entity entity, gfx::SpotLight&& newData)
{
    //TODO: logic for managing mutliple spotlights

    entityManager->addComponentData(entity, std::move(newData));
}

void LightingSystem::addPointLight(EntityManager* entityManager, Entity entity, gfx::PointLight&& newData)
{
    newData.shaderIndex = pointLightCount;

    if (entityManager->addComponentData(entity, std::move(newData)))
    {
        ++pointLightCount;
    }
}

void LightingSystem::addDirectionalLight(EntityManager* entityManager, Entity entity, gfx::DirectionalLight&& newData)
{
    //TODO: logic for managing mutliple directional lights

    entityManager->addComponentData(entity, std::move(newData));
}

void LightingSystem::iterateDirectionalLightPool(ComponentManager<gfx::DirectionalLight>* pool, Shader* shader)
{
    if(pool == nullptr)
    {
        #ifdef ENABLE_DEBUG_MESSAGES
            std::cout << "DEBUG::LightingSystem::iterateDirectionalLightPool::No directional light pool" << std::endl;
        #endif
        return;
    }

    std::vector<gfx::DirectionalLight>::iterator poolBegin = pool->begin();
    std::vector<gfx::DirectionalLight>::iterator poolEnd = pool->end();

    //TODO: At the moment the last read directional component will be applied
    for (auto directionalLightIter = poolBegin; directionalLightIter != poolEnd; ++directionalLightIter)
    {
        shader->updateUniformValue("directionalLight.direction",                directionalLightIter->direction);
        shader->updateUniformValue("directionalLight.lightColours.ambient",     directionalLightIter->lightColours.ambient);
        shader->updateUniformValue("directionalLight.lightColours.diffuse",     directionalLightIter->lightColours.diffuse);
        shader->updateUniformValue("directionalLight.lightColours.specular",    directionalLightIter->lightColours.specular);
    }
}

void LightingSystem::iteratePointLightPool(ComponentManager<gfx::PointLight>* pool, Shader* shader)
{
    if(pool == nullptr)
    {
        #ifdef ENABLE_DEBUG_MESSAGES
            std::cout << "DEBUG::LightingSystem::iteratePointLightPool::No point light pool" << std::endl;
        #endif
        return;
    }

    std::vector<gfx::PointLight>::iterator poolBegin = pool->begin();
    std::vector<gfx::PointLight>::iterator poolEnd = pool->end();

    for (auto pointLightIter = poolBegin; pointLightIter != poolEnd; ++pointLightIter)
    {
        std::string accessString = "pointLights[" + std::to_string(pointLightIter->shaderIndex) + "].lightColours.ambient";
        shader->updateUniformValue(accessString.c_str(), pointLightIter->lightColours.ambient);

        accessString = "pointLights[" + std::to_string(pointLightIter->shaderIndex) + "].lightColours.diffuse";
        shader->updateUniformValue(accessString.c_str(), pointLightIter->lightColours.diffuse);

        accessString = "pointLights[" + std::to_string(pointLightIter->shaderIndex) + "].lightColours.specular";
        shader->updateUniformValue(accessString.c_str(), pointLightIter->lightColours.specular);

        accessString = "pointLights[" + std::to_string(pointLightIter->shaderIndex) + "].position";
        shader->updateUniformValue(accessString.c_str(), pointLightIter->position);

        accessString = "pointLights[" + std::to_string(pointLightIter->shaderIndex) + "].constants.constant";
        shader->updateUniformValue(accessString.c_str(), pointLightIter->constants.constant);

        accessString = "pointLights[" + std::to_string(pointLightIter->shaderIndex) + "].constants.linear";
        shader->updateUniformValue(accessString.c_str(), pointLightIter->constants.linear);

        accessString = "pointLights[" + std::to_string(pointLightIter->shaderIndex) + "].constants.quadratic";
        shader->updateUniformValue(accessString.c_str(), pointLightIter->constants.quadratic);
    }
}

void LightingSystem::iterateSpotLightPool(ComponentManager<gfx::SpotLight>* pool, Shader* shader)
{
    if(pool == nullptr)
    {
        #ifdef ENABLE_DEBUG_MESSAGES
            std::cout << "DEBUG::LightingSystem::iteratePointLightPool::No point light pool" << std::endl;
        #endif
        return;
    }

    std::vector<gfx::SpotLight>::iterator poolBegin = pool->begin();
    std::vector<gfx::SpotLight>::iterator poolEnd = pool->end();

    //TODO: At the moment the last read point component will be applied
    for (auto spotLightIter = poolBegin; spotLightIter != poolEnd; ++spotLightIter)
    {
        shader->updateUniformValue("spotLight.lightColours.ambient",    spotLightIter->lightColours.ambient);
        shader->updateUniformValue("spotLight.lightColours.diffuse",    spotLightIter->lightColours.diffuse);
        shader->updateUniformValue("spotLight.lightColours.specular",   spotLightIter->lightColours.specular);
        shader->updateUniformValue("spotLight.position",                spotLightIter->position);
        shader->updateUniformValue("spotLight.direction",               spotLightIter->direction);
        shader->updateUniformValue("spotLight.cutOff.inner",            spotLightIter->cutOff.inner);
        shader->updateUniformValue("spotLight.cutOff.outer",            spotLightIter->cutOff.outer);
    }
}

void LightingSystem::refreshUniforms(Shader* shader, EntityManager* entityManager)
{
    shader->updateUniformValue("numberOfActiveLights", pointLightCount);

    auto directionalLightPool = entityManager->getComponentPool<gfx::DirectionalLight>();

    iterateDirectionalLightPool(directionalLightPool, shader);

    auto pointLightPool = entityManager->getComponentPool<gfx::PointLight>();

    iteratePointLightPool(pointLightPool, shader);

    auto spotLightPool = entityManager->getComponentPool<gfx::SpotLight>();

    iterateSpotLightPool(spotLightPool, shader);
}

}