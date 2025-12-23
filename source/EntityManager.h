#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <stdint.h>
#include <vector> 

class EntityManager
{
    public:
        EntityManager();
        uint32_t getNewID();
        void deleteEntity(uint32_t entity);
        size_t getEntityPosition(uint32_t entity);

    private:
        uint32_t nextID;
        std::vector<uint32_t> recyclingBucket;
        std::vector<uint32_t> activeIDs;



};



#endif 