#include "Model.h"

namespace gfx
{


Model::Model(ModelInitData initData)
{
    //position
    objectTransforms = initData.transform;

    reconstructModelMatrix();
    
    // For meshes in mesh init vector - create mesh object
    for (const auto& materialMeshPair : initData.materialMeshPairs)
    {
        std::unique_ptr<Material> newMaterialInstance = std::make_unique<Material>(materialMeshPair.material);
        Material* materialRaw = newMaterialInstance.get();
        materials.push_back(std::move(newMaterialInstance));

        std::unique_ptr<Mesh> newMeshInstance = std::make_unique<Mesh>(materialMeshPair.meshData);
        Mesh* meshRaw = newMeshInstance.get();
        meshes.push_back(std::move(newMeshInstance));

        Part newPart;
        newPart.material = materialRaw;
        newPart.mesh = meshRaw;

        parts.push_back(newPart);
    }
}

void Model::reconstructModelMatrix()
{
    // Rebuild matrix from scratch every time to prevent error accumulation on it
    modelMatrix = glm::mat4(1.0f);

    // Translate
    modelMatrix = glm::translate(modelMatrix, objectTransforms->position);

    // Rotate in the order X -> Y -> Z every time
    modelMatrix = glm::rotate(modelMatrix, glm::radians(objectTransforms->rotation.x), glm::vec3{1.0f, 0.0f, 0.0f}); // x rotation
    modelMatrix = glm::rotate(modelMatrix, glm::radians(objectTransforms->rotation.y), glm::vec3{0.0f, 1.0f, 0.0f}); // y rotation
    modelMatrix = glm::rotate(modelMatrix, glm::radians(objectTransforms->rotation.z), glm::vec3{0.0f, 0.0f, 1.0f}) ; // z rotation

    // Scale
    modelMatrix = glm::scale(modelMatrix, objectTransforms->scaleFactors);
}

void Model::drawModel()
{
    reconstructModelMatrix();

    for (const auto& part : parts)
    {
        part.material->shader->useProgram();

        if (!part.material->isLightSource)
        {
            part.material->shader->updateUniformValue("objectColor", glm::vec3{1.0f, 0.5f, 0.31f});
            part.material->shader->updateUniformValue("lightColor",  glm::vec3{1.0f, 1.0f, 1.0f});
        }

        //TODO: also set texture here
        part.material->shader->updateModelMatrixValue(modelMatrix);
        part.mesh->drawMesh();
    }
}

}