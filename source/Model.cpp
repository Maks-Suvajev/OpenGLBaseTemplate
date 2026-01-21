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

            //part.material->shader->updateUniformValue("material.shininess", part.material->materialProp.shininess);
            part.material->shader->updateUniformValue("material.shininess", part.material->materialProp.shininess);



            // Time vary colours
            glm::vec3 lightColor{1.0f};
            // lightColor.x = static_cast<float>(sin(glfwGetTime() * 2.0f));
            // lightColor.y = static_cast<float>(sin(glfwGetTime() * 0.7f));
            // lightColor.z = static_cast<float>(sin(glfwGetTime() * 1.3f));

            glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
            glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);

            // Set diffusion texture here
            part.material->shader->updateUniformValue("material.diffuse", 0);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, part.material->materialProp.diffuse);

            part.material->shader->updateUniformValue("material.specular", 1);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, part.material->materialProp.specular);




            //part.material->shader->updateUniformValue("objectColor", glm::vec3{1.0f, 0.5f, 0.31f});
            part.material->shader->updateUniformValue("spotLight.ambient",   ambientColor);
            part.material->shader->updateUniformValue("spotLight.diffuse",   diffuseColor);
            part.material->shader->updateUniformValue("spotLight.specular",  lightColor);

            part.material->shader->updateUniformValue("pointLights[0].ambient",   ambientColor);
            part.material->shader->updateUniformValue("pointLights[0].diffuse",   diffuseColor);
            part.material->shader->updateUniformValue("pointLights[0].specular",  lightColor);
            part.material->shader->updateUniformValue("pointLights[0].position",  glm::vec3(1.2f, 1.0, 2.0f));

            part.material->shader->updateUniformValue("pointLights[0].constant",  1.0f);
            part.material->shader->updateUniformValue("pointLights[0].linear",  0.09f);
            part.material->shader->updateUniformValue("pointLights[0].quadratic",  0.032f);

            part.material->shader->updateUniformValue("directionalLight.direction",   glm::vec3(-0.2f, -1.0f, -0.3f));
            part.material->shader->updateUniformValue("directionalLight.ambient",   ambientColor);
            part.material->shader->updateUniformValue("directionalLight.diffuse",   diffuseColor);
            part.material->shader->updateUniformValue("directionalLight.specular",  lightColor);

        }

        //TODO: also set texture here
        part.material->shader->updateModelMatrixValue(modelMatrix);
        part.mesh->drawMesh();
    }
}


std::vector<Material*> Model::getMaterials()
{
    std::vector<Material*> ptrsToMaterials;
    ptrsToMaterials.reserve(materials.size());

    for (const auto& material : materials)
    {
        ptrsToMaterials.push_back(material.get());
    }

    return ptrsToMaterials;
}

}