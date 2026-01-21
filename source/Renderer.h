#ifndef RENDERER_H
#define RENDERER_H

#include "Model.h"
#include <memory>

namespace gfx
{

class Renderer
{

    public:
        Renderer(std::vector<ModelInitData> modelsToInit);

        void drawScene()
        {
            for (const auto& model : models)
            {
                model->drawModel();
            }
        }

        // Specular calculations require camera position in order to make the calculation.
        void updateViewPosForSpecularLight(glm::vec3 cameraPos);



    private:
    
















};


}

#endif