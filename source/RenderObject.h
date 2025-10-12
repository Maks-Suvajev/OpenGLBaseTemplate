#ifndef RENDEROBJECT_H
#define RENDEROBJECT_H


#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>



namespace gfx {

template<typename T>
struct PositionAndTextureInstance; // Use forward declaration 

// Template for 2D or 3D
template<typename T>
class RenderObject
{
    public:
        RenderObject(PositionAndTextureInstance<T> initValues){

            position = initValues.position;
            textures = initValues.textureIndices;

            scaleFactor = 1; // default value for now

            std::cout << "Instantiated new render object with position: ";


            std::cout << "PosX = " << position.x << " " << "PosY = " << position.y << " " << "PosZ = " << position.z;
   

            std::cout << std::endl;

            std::cout << "And texture Indices: ";

            for (auto& index : textures)
            {
                std::cout << " " << index << " ";
            }

            std::cout << std::endl;

        }


        T getPosition(){return position;}
        unsigned int getScaleFactor(){return scaleFactor;}
        
    private:
        T position;
        std::vector<uint32_t> textures; //indices for which VAO loaded textures 
        unsigned int scaleFactor;
};

}

#endif