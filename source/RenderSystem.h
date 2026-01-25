#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include "Renderer.h"
#include "EntityManager.h"

namespace gfx
{

class RenderSystem
{
    public:
        RenderSystem() = default;

    private:
        void runRender(Renderer& renderer, EntityManager& entityManager);

};

}

#endif