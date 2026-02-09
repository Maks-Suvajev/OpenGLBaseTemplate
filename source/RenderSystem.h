#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include "Renderer.h"

// system
#include "Window.h"

// Resource managers
#include "EntityManager.h"
#include "ShaderManager.h"

// Component Types
#include "PhysicsTypes.h"
#include "MaterialTypes.h"

// Maths
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace gfx
{

class RenderSystem
{
    public:
        RenderSystem() = default;
        void runRender(Window* window, Renderer* renderer, EntityManager* entityManager, ShaderManager* shaderManager);

    private:
        glm::mat4& updateAndGetModelMatrix(std::vector<gfx::Transform>::iterator& transformIter);

        template<typename T>
        T* getPoolElement(Entity entity, EntityManager* entityManager);
};

template<typename T>
T* RenderSystem::getPoolElement(Entity entity, EntityManager* entityManager)
{
    auto pool = entityManager->getComponentPool<T>();

    if (pool == nullptr)
    {
        #ifdef ENABLE_DEBUG_MESSAGES
            std::cout << "ERROR::RenderSystem::getPoolElement::No pool for type found: " << typeid(T).name() << std::endl;
        #endif
    }

    auto component = pool->getComponentData(entity);

    if (component == nullptr)
    {
        #ifdef ENABLE_DEBUG_MESSAGES
            std::cout << "ERROR::RenderSystem::getPoolElement::Entity component has no value for some reason." << std::endl;
        #endif

        return nullptr;        
    }
    
    return component;
}

}

#endif