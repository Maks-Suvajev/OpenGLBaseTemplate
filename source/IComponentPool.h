#ifndef ICOMPONENT_POOL
#define ICOMPONENT_POOL

#include "EntityManager.h"

class IComponentPool
{
    public:
        virtual  ~IComponentPool() = default;

        virtual void destroyEntity(Entity entity) = 0;
};


#endif