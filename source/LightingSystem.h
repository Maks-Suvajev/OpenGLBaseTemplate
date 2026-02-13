#ifndef LIGHTING_SYSTEM_H
#define LIGHTING_SYSTEM_H

//STL
#include <cstdint>
#include <string>

#include "Shader.h"
#include "ComponentManager.h"
#include "EntityManager.h"

#include "LightTypes.h"

namespace gfx
{

class LightingSystem
{
    public:
        LightingSystem();
        void refreshUniforms(Shader* shader, EntityManager* entityManager);
        void addSpotLight(EntityManager* entityManager, Entity entity, gfx::SpotLight&& newData);
        void addPointLight(EntityManager* entityManager, Entity entity, gfx::PointLight&& newData);
        void addDirectionalLight(EntityManager* entityManager, Entity entity, gfx::DirectionalLight&& newData);

    private:
        int pointLightCount; // Number of active point lights

        void iterateDirectionalLightPool(ComponentManager<gfx::DirectionalLight>* pool, Shader* shader);
        void iteratePointLightPool(ComponentManager<gfx::PointLight>* pool, Shader* shader);
        void iterateSpotLightPool(ComponentManager<gfx::SpotLight>* pool, Shader* shader);
};

}

#endif