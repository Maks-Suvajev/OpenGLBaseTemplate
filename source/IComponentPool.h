#ifndef ICOMPONENT_POOL
#define ICOMPONENT_POOL


class IComponentPool
{
    public:
       virtual  ~IComponentPool() = default;

        virtual void destroyEntity(uint32_t entity) = 0;
};


#endif