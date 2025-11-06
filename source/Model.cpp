#include "Model.h"

namespace gfx
{


Model::Model(ModelInitData initData)
{
    //position
    objectTransforms = initData.transform;

    reconstructModelMatrix();
    
    // For meshes in mesh init vector - create mesh object
    for (const auto& meshInstance : initData.meshInitData)
    {
        std::unique_ptr<Mesh> newMeshInstance = std::make_unique<Mesh>(meshInstance);
        Meshes.push_back(newMeshInstance);
    }

}

void Model::reconstructModelMatrix()
{
    // Rebuild matrix from scratch every time to prevent error accumulation on it
    modelMatrix = glm::mat4(1.0f);

    // Translate
    modelMatrix = glm::translate(modelMatrix, objectTransforms.position);

    // Rotate in the order X -> Y -> Z every time
    modelMatrix = glm::rotate(modelMatrix, glm::radians(objectTransforms.rotation.x), glm::vec3{1.0f, 0.0f, 0.0f}); // x rotation
    modelMatrix = glm::rotate(modelMatrix, glm::radians(objectTransforms.rotation.y), glm::vec3{0.0f, 1.0f, 0.0f}); // y rotation
    modelMatrix = glm::rotate(modelMatrix, glm::radians(objectTransforms.rotation.z), glm::vec3{0.0f, 0.0f, 1.0f}) ; // z rotation
}

}