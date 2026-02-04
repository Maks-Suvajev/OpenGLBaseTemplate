#ifndef RENDERER_H
#define RENDERER_H

#include <memory>

#include "MeshTypes.h"


//TODO:: Modify renderer to take in gpuhandles from mesh types


namespace gfx
{

class Renderer
{

    public:
        Renderer() = default;

        void renderHandle(GpuHandles& handle);
        void bindVAO(GLuint VAO);

        // Specular calculations require camera position in order to make the calculation.
        //void updateViewPosForSpecularLight(glm::vec3 cameraPos);



    private:
    
















};


}

#endif