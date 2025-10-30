#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <filesystem>
#include "TextureLoader.h"
#include <iostream>
#include "Shader.h"
#include "VAOGroup.h"
#include "RenderObject.h"


namespace gfx {

template<typename T>
class Renderer
{
    public:
        Renderer(std::vector<VAOGroupData<T>>&& VAOInitData, std::vector<std::filesystem::path>& texturePaths, Shader& shader);
        //void loadVAOList(std::vector<VAOGroup<T>>&& VAOList);
        void drawScene(Shader& shaderInstance, Window& windowInstance);
        void rebindTextures();
        std::vector<std::shared_ptr<RenderObject<T>>> getMovableObjects();
        

    private:
        std::vector<std::unique_ptr<VAOGroup<T>>> VAOGroups;
        std::vector<GLuint> textureIDs;
        GLint maxTextureUnits;

};


// Flatten all objects into a single vector for sending their pointers to movement/physics systems
template<typename T>
std::vector<std::shared_ptr<RenderObject<T>>> Renderer<T>::getMovableObjects()
{
    std::vector<std::shared_ptr<RenderObject<T>>> moveableObjects;
    std::vector<std::shared_ptr<RenderObject<T>>> tempInstanceList;

    for (auto& VAOGroup : VAOGroups)
    {
        tempInstanceList = VAOGroup->shareInstanceList();
        moveableObjects.insert(moveableObjects.end(), tempInstanceList.begin(), tempInstanceList.end());
    }

    return moveableObjects;
}


template<typename T>
Renderer<T>::Renderer(std::vector<VAOGroupData<T>>&& VAOInitData, std::vector<std::filesystem::path>& texturePaths, Shader& shader)
{
    // Load VAOs
    for(auto& VAOInitInstance : VAOInitData)
    {
        std::unique_ptr<VAOGroup<T>> newGroup = VAOGroup<T>::template create(std::move(VAOInitInstance));
        VAOGroups.push_back(std::move(newGroup));
    }

    // Pull max number of texture units
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxTextureUnits);
    #ifdef ENABLE_DEBUG_MESSAGES
        std::cout << "DEBUG::Detected max texture units as = " << maxTextureUnits << std::endl;
    #endif

    // Load textures
    GLuint textureID;

    for(const auto& path : texturePaths)
    {
        if (textureIDs.size() >= maxTextureUnits)
        {
            #ifdef ENABLE_DEBUG_MESSAGES
                std::cout << "DEBUG::Max number of texture units reached (" << maxTextureUnits << "). Cannot load any more textures" << std::endl;
            #endif

            break;
        }

        textureID = loadTexture(path);

        if (textureID != 0)
        {
            glActiveTexture(GL_TEXTURE0 + static_cast<GLenum>(textureIDs.size()));
            glBindTexture(GL_TEXTURE_2D, textureID);

            #ifdef ENABLE_DEBUG_MESSAGES
                std::cout << "DEBUG::Bound texture: " << GL_TEXTURE0 + static_cast<GLenum>(textureIDs.size()) << std::endl;
                std::cout << "DEBUG::To textureID = " << textureID << std::endl;
            #endif

            textureIDs.push_back(textureID);
        }
        else
        {
            #ifdef ENABLE_DEBUG_MESSAGES
                std::cout << "DEBUG::Failed to load texture with path: " << path.string() << std::endl;
            #endif
        }
    }

    // Update uniform 
    
    // Build binding array for texture array uniform
    std::vector<GLint> textureUnits(textureIDs.size());
    for (GLuint textureUnit = 0; textureUnit < textureIDs.size(); ++textureUnit)
    {
        textureUnits[textureUnit] = textureUnit;
    }

    #ifdef ENABLE_DEBUG_MESSAGES
        std::cout << "DEBUG::Texture uniform built: ";

        for (auto& i : textureUnits)
        {
            std::cout << " " << i << " ";
        }

        std::cout << std::endl;
    #endif

    shader.useProgram();

    GLint texturesUniformLoc = shader.getUniformLocation("textures");

    if (texturesUniformLoc == -1)
    {
        #ifdef ENABLE_DEBUG_MESSAGES
            std::cout << "ERROR::FAILED TO LOAD TEXTURES UNIFORM LOCATION!" << std::endl;
        #endif
    }
    else
    {
        glUniform1iv(texturesUniformLoc, static_cast<GLsizei>(textureUnits.size()), textureUnits.data());
        
        GLenum err = glGetError();
        if (err != GL_NO_ERROR)
        {
            #ifdef ENABLE_DEBUG_MESSAGES
                std::cout << "ERROR::glUniform1iv failed to set texture uniform with error: " << err << std::endl;
            #endif
        }
        else
        {
            #ifdef ENABLE_DEBUG_MESSAGES
                std::cout << "DEBUG::glUniform1iv succeeded in setting texture uniform!" << std::endl;
            #endif
        }
    }

}

template<typename T>
void Renderer<T>::rebindTextures()
{
    for (size_t i = 0; i < textureIDs.size(); ++i)
    {
        glActiveTexture(GL_TEXTURE0 + static_cast<GLenum>(i));
        glBindTexture(GL_TEXTURE_2D, textureIDs[i]);
    }
}

template<typename T>
void Renderer<T>::drawScene(Shader& shaderInstance, Window& windowInstance)
{
    shaderInstance.useProgram();

    rebindTextures(); // all instances sharing texture now

   for (auto& VAOGroup : VAOGroups)
   {
        VAOGroup->drawGroup(shaderInstance, windowInstance);
   }
}

}

#endif


