#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <stdint.h>
#include <vector> 
#include <unordered_map>
#include <typeindex>
#include <typeinfo>

#include "ComponentManager.h"

#include "Entity.h"

class EntityManager
{
    public:
        EntityManager();
        Entity getNewID();
        void deleteEntity(Entity entity);
        Entity generateNewEntity();

        void printActiveEntityIDs();
        void printActiveEntityComponents(Entity entity);

        template<typename T>
        void addComponentData(Entity entity, T&& componentData);

        template<typename T>
        std::optional<T&> getComponentData(Entity entity);

        template<typename T>
        ComponentManager<T>* getComponentPool();

    private:
        void resizeSparse(Entity entity);
        uint32_t nextID;
        std::vector<Entity> recyclingBucket;
        std::vector<Entity> activeIDs;
        std::vector<Entity> sparse;
        std::unordered_map<std::type_index, std::unique_ptr<IComponentPool>> componentPools;
};



template<typename T>
void EntityManager::addComponentData(Entity entity, T&& componentData)
{
    auto index = std::type_index(typeid(T));

    if (!componentPools.contains(index))
    {
        componentPools[index] = std::make_unique<ComponentManager<T>>();
    }

    static_cast<ComponentManager<T>*>(componentPools[index].get())->addComponent(entity, std::move(componentData));
}

template<typename T>
std::optional<T&> EntityManager::getComponentData(Entity entity)
{
    auto index = std::type_index(typeid(T));

    if (!componentPools.contains(index))
    {
        #ifdef ENABLE_DEBUG_MESSAGES
            std::cout << "ERROR::EntityManager::Component requested doesn't exist and has no pool." << std::endl;
        #endif

        return std::nullopt;
    }

    auto componentRef = static_cast<ComponentManager<T>*>(componentPools[index].get())->getComponentData(entity);

    if (componentRef)
    {
        return componentRef;
    }
    else
    {
        #ifdef ENABLE_DEBUG_MESSAGES
            std::cout << "ERROR::EntityManager::Entity does not have this component" << std::endl;
        #endif

        return std::nullopt;
    }
} 

template<typename T>
ComponentManager<T>* EntityManager::getComponentPool()
{
    auto index = std::type_index(typeid(T));

    if (!componentPools.contains(index))
    {
        #ifdef ENABLE_DEBUG_MESSAGES
            std::cout << "ERROR::EntityManager::Component requested doesn't exist and has no pool." << std::endl;
        #endif

        return nullptr;
    }

    return static_cast<ComponentManager<T>*>(componentPools[index].get());
}


#endif