#include "EntityManager.h"

EntityManager::EntityManager()
{
    nextID = 0;
}

uint32_t EntityManager::getNewID()
{
    if (recyclingBucket.empty())
    {
        return nextID++;
    }

    uint32_t newID = recyclingBucket.back();
    recyclingBucket.pop_back();

    return newID;
}

void EntityManager::deleteEntity(uint32_t entity)
{
    size_t position = getEntityPosition(entity); // get position
    std::swap(activeIDs[position], activeIDs.back()); // swap with back of vector
    activeIDs.pop_back(); // remove from back

    recyclingBucket.push_back(entity); 

}

size_t EntityManager::getEntityPosition(uint32_t entity)
{
    auto it = std::find(activeIDs.begin(), activeIDs.end(), entity);

    if (it != activeIDs.end())
    {
        return (it - activeIDs.begin());
    }

    #ifdef ENABLE_DEBUG_MESSAGES
        std::cout << "ERROR::Entity not found returning UINT32_MAX because something has gone wrong." << std::endl;
    #endif

    return UINT32_MAX; // Need a handler for this error;
}

