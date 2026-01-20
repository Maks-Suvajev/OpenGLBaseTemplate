#ifndef COMPONENT_MANAGER
#define COMPONENT_MANAGER

#include <vector>
#include "IComponentPool.h"

constexpr uint32_t initialSparseCapacity = 10000U;

template<typename T>
class ComponentManager : public IComponentPool
{
    public:
        ComponentManager();


    private:
        void initSparseArray(size_t size);
        void resizeSparse(uint32_t entity);
        void addComponent(uint32_t entity, T&& newData);
        void deleteComponent(uint32_t entity);

        void destroyEntity(uint32_t) override;

        std::vector<T> dense;
        std::vector<uint32_t> denseMap; // Maps denseMap structure denseMap[0] tells you what entity is at pos 0 in dense
        std::vector<uint32_t> sparse; // Maps entityID to position in denseMap i.e. sparse[2] tells you where entity 2 component is

};

template<typename T>
void ComponentManager<T>::deleteComponent(uint32_t entity)
{
    uint32_t indexToRemove = sparse[entity];
    uint32_t entityAtBack = denseMap.back();
    
    dense[indexToRemove] = dense.back();
    denseMap[indexToRemove] = entityAtBack;
    sparse[entityAtBack] = indexToRemove;
    
    dense.pop_back();
    denseMap.pop_back();
    sparse[entity] = UINT32_MAX;
}

template<typename T>
void ComponentManager<T>::initSparseArray(size_t size)
{
    sparse.assign(size, UINT32_MAX);
}

template<typename T>
ComponentManager<T>::ComponentManager()
{
    initSparseArray(initialSparseCapacity);
}

template<typename T>
void ComponentManager<T>::resizeSparse(uint32_t entity)
{
    // Double the size of the sparse vector unless entityID is higher
    size_t newSize = std::max(static_cast<size_t>(entity + 1), static_cast<size_t>(sparse.size()) * 2);

    sparse.resize(newSize, UINT32_MAX);
}


template<typename T>
void ComponentManager<T>::addComponent(uint32_t entity, T&& newData)
{
    if (entity >= sparse.size())
    {
        resizeSparse(entity);
    }

    if (sparse[entity] == UINT32_MAX)
    {
        dense.push_back(std::move(newData));

        denseMap.push_back(entity);

        sparse[entity] = dense.size() - 1;
    }
    else 
    {
        #ifdef ENABLE_DEBUG_MESSAGES
            std::cout << "ERROR::Entity already exists - doing nothing." << std::endl;
        #endif
    }
}

#endif