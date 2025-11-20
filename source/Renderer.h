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



    private:
        std::vector<std::unique_ptr<Model>> models;
    
















};


}

#endif