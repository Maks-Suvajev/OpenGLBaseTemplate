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

struct Material
{
    Shader* shader;
    GLuint texture;
    bool isLightSource;
};

struct Part
{
    Material* material;
    Mesh* mesh;
};

struct MaterialMeshPair
{
    Material material;
    MeshData meshData;
};


struct ModelInitData
{
    Transform* transform;
    std::vector<MaterialMeshPair> materialMeshPairs;
};



class Model
{
    public:
        Model(ModelInitData initData);

        void drawModel();

        std::vector<Material*> getMaterials();

        // Commenting out before deletion (will be moved to object handler system)
        /*
        const Transform& getTransform() const
        {
            return objectTransforms;
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

        */

    private:
        Transform * objectTransforms; 
        glm::mat4 modelMatrix; 
        std::vector<std::unique_ptr<Mesh>> meshes;
        std::vector<std::unique_ptr<Material>> materials;
        std::vector<Part> parts;

        void reconstructModelMatrix();
};

}

#endif