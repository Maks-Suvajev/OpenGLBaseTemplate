#include <iostream>
#include "EntityManager.h"

EntityManager::EntityManager()
{
    nextID = 0;
}

void EntityManager::generateNewEntity()
{
    uint32_t newID = getNewID();

    activeIDs.push_back(newID);
    sparse[newID] = static_cast<uint32_t>(activeIDs.size() - 1);
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
    uint32_t position = sparse[entity]; // get position
    uint32_t backValue = activeIDs.back(); // get back value

    activeIDs[position] = backValue; // Move back data into position of deleted data
    sparse[backValue] = position;

    activeIDs.pop_back(); // remove from back ID

    sparse[entity] = UINT32_MAX;

    recyclingBucket.push_back(entity); 

    // Delete it in all pools
    for (auto& [key, componentPool] : componentPools)
    {
        componentPool->destroyEntity(entity);
    }

}