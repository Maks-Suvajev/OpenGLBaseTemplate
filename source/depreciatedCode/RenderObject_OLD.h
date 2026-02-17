#ifndef RENDEROBJECT_H
#define RENDEROBJECT_H


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>



namespace gfx {

template<typename T>
struct PositionAndTextureInstance; // Use forward declaration 

template<typename T>
struct Transform
{
    T position;
    T rotation; //Euler rotation
    T scaleFactors;
};

// Template for 2D or 3D
template<typename T>
class RenderObject
{
    public:
        RenderObject(PositionAndTextureInstance<T> initValues){

            textures = initValues.textureIndices;

            objectTransforms.position = initValues.position;
            objectTransforms.scaleFactors = T{1.0}; // default value for now
            objectTransforms.rotation = T{0.0}; // default value for now

            modelMatrix = glm::mat4(1.0f);

            #ifdef ENABLE_DEBUG_MESSAGES
                std::cout << "DEBUG::Instantiated new render object with position: ";
                std::cout << "DEBUG::PosX = " << objectTransforms.position.x << " " << "PosY = " << objectTransforms.position.y << " " << "PosZ = " << objectTransforms.position.z << std::endl;

                std::cout << "DEBUG::And texture Indices: ";

                for (auto& index : textures)
                {
                    std::cout << " " << index << " ";
                }

                std::cout << std::endl;
            #endif
        }

        glm::mat4 getModelMatrix()
        {
            return modelMatrix;
        }

        void updateModelMatrix(glm::mat4 newModelMatrix)
        {
            modelMatrix = newModelMatrix;
        }

        T getPosition()
        {
            return objectTransforms.position;
        }

        T getRotation()
        {
            return objectTransforms.rotation;
        }

        T getScaleFactors()
        {
            return objectTransforms.scaleFactors;
        }

        void updatePosition(T newPosition)
        {
            objectTransforms.position = newPosition;
        }

        void updateRotation(T newRotation)
        {
            objectTransforms.rotation = newRotation;
        }

        void updateScaleFactors(T newScaleFactors)
        {
            objectTransforms.scaleFactors = newScaleFactors;
        }
        
    private:
        Transform<T> objectTransforms;
        glm::mat4 modelMatrix;
        std::vector<uint32_t> textures; //indices for which VAO loaded textures 
};

}

#endif