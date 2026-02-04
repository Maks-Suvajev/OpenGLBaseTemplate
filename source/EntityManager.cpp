#include <iostream>
#include "EntityManager.h"

EntityManager::EntityManager()
: nextID(0U)
{
}

Entity EntityManager::generateNewEntity()
{
    Entity newID = getNewID();

    activeIDs.push_back(newID);
    sparse[newID] = static_cast<Entity>(activeIDs.size() - 1);

    return newID;
}

Entity EntityManager::getNewID()
{
    if (recyclingBucket.empty())
    {
        return nextID++;
    }

    Entity newID = recyclingBucket.back();
    recyclingBucket.pop_back();

    return newID;
}

void EntityManager::deleteEntity(Entity entity)
{
    Entity position = sparse[entity]; // get position
    Entity backValue = activeIDs.back(); // get back value

    activeIDs[position] = backValue; // Move back data into position of deleted data
    sparse[backValue] = position;

    activeIDs.pop_back(); // remove from back ID

    sparse[entity] = maxEntityValue;

    recyclingBucket.push_back(entity); 

    // Delete it in all pools
    for (auto& [key, componentPool] : componentPools)
    {
        componentPool->destroyEntity(entity);
    }

}