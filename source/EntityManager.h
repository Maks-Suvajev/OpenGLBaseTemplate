#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <stdint.h>
#include <vector> 
#include <unordered_map>
#include <typeindex>
#include <typeinfo>
#include "ComponentManager.h"

class EntityManager
{
    public:
        EntityManager();
        uint32_t getNewID();
        void deleteEntity(uint32_t entity);
        void generateNewEntity();


        template<typename T>
        void addComponentData(uint32_t entity, T componentData);

    private:
        uint32_t nextID;
        std::vector<uint32_t> recyclingBucket;
        std::vector<uint32_t> activeIDs;
        std::vector<uint32_t> sparse;
        std::unordered_map<std::type_index, std::unique_ptr<IComponentPool>> componentPools;
};

template<typename T>
void EntityManager::addComponentData(uint32_t entity, T componentData)
{
    auto index = std::type_index(typeid(T));

    auto it = componentPools.find(index);

    if (it == componentPools.end())
    {
        componentPools[index] = std::make_unique<ComponentManager<T>>();
    }

    static_cast<ComponentManager<T>*>(componentPools[index].get())->addComponent(entity, componentData);
}


#endif 