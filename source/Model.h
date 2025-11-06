#ifndef MODEL_H
#define MODEL_H

#include "Mesh.h"
#include <glm/glm.hpp>


namespace gfx
{

struct Transform
{
    glm::vec3 position;
    glm::vec3 rotation; //Euler rotation
    glm::vec3 scaleFactors;
};

struct ModelInitData
{
    Transform transform;
    std::vector<MeshData> meshInitData;

};

class Model
{
    public:
        Model(ModelInitData initData);

        // Getters
        const glm::mat4& getModelMatrix() const
        {
            return modelMatrix;
        }

        const Transform& getTransform() const
        {
            return objectTransforms;
        }

        // Setters
        void updateModelMatrix(glm::mat4 newModelMatrix)
        {
            modelMatrix = newModelMatrix;
        }

        void updatePosition(glm::vec3 newPosition)
        {
            objectTransforms.position = newPosition;
        }

        void updateRotation(glm::vec3 newRotation)
        {
            objectTransforms.rotation = newRotation;
        }

        void updateScaleFactors(glm::vec3 newScaleFactors)
        {
            objectTransforms.scaleFactors = newScaleFactors;
        }


    private:
        Transform objectTransforms;
        glm::mat4 modelMatrix;
        std::vector<std::unique_ptr<Mesh>> Meshes;

        void reconstructModelMatrix();
};

}

#endif