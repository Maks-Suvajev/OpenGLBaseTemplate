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



namespace gfx {

//TODO: Currently using texture unit indexing, need to switch to texture arrays or I can only bind 16 or 32 texturesm, horrible limitation
// Holds an objects position and which loaded textures should be bound with that particular object
template<typename T>
class Renderer
{
    public:
        Renderer(std::vector<VAOGroupData<T>>&& VAOInitData, std::vector<std::filesystem::path>&& texturePaths, Shader& shader);
        //void loadVAOList(std::vector<VAOGroup<T>>&& VAOList);
        void drawScene(Shader& shaderInstance, Window& windowInstance);
        void rebindTextures();
        

    private:
        std::vector<std::unique_ptr<VAOGroup<T>>> VAOGroups;
        std::vector<GLuint> textureIDs;
        GLint maxTextureUnits;

};

template<typename T>
Renderer<T>::Renderer(std::vector<VAOGroupData<T>>&& VAOInitData, std::vector<std::filesystem::path>&& texturePaths, Shader& shader)
{
    // Load VAOs
    for(auto& VAOInitInstance : VAOInitData)
    {
        std::unique_ptr<VAOGroup<T>> newGroup = VAOGroup<T>::template create(std::move(VAOInitInstance));
        VAOGroups.push_back(std::move(newGroup));
    }

    // Pull max number of texture units
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxTextureUnits);

    std::cout << "Detected max texture units as = " << maxTextureUnits << std::endl;

    // Load textures
    GLuint textureID;

    for(const auto& path : texturePaths)
    {
        if (textureIDs.size() >= maxTextureUnits)
        {
            std::cout << "Max number of texture units reached (" << maxTextureUnits << "). Cannot load any more textures" << std::endl;
            break;
        }

        textureID = loadTexture(path);

        if (textureID != 0)
        {
            glActiveTexture(GL_TEXTURE0 + static_cast<GLenum>(textureIDs.size()));
            glBindTexture(GL_TEXTURE_2D, textureID);

            std::cout << "Bound texture: " << GL_TEXTURE0 + static_cast<GLenum>(textureIDs.size()) << std::endl;
            std::cout << "To textureID = " << textureID << std::endl;

            textureIDs.push_back(textureID);
        }
        else
        {
            std::cout << "Failed to load texture with path: " << path.string() << std::endl;
        }
    }

    // Update uniform 
    
    // Build binding array for texture array uniform
    std::vector<GLint> textureUnits(textureIDs.size());
    for (GLuint textureUnit = 0; textureUnit < textureIDs.size(); ++textureUnit)
    {
        textureUnits[textureUnit] = textureUnit;
    }

    std::cout << "Texture uniform built: ";

    for (auto& i : textureUnits)
    {
        std::cout << " " << i << " ";
    }

    std::cout << std::endl;

    shader.useProgram();

    GLint texturesUniformLoc = shader.getUniformLocation("textures");

    if (texturesUniformLoc == -1)
    {
        std::cout << "FAILED TO LOAD TEXTURES UNIFORM LOCATION!" << std::endl;
    }
    else
    {
        glUniform1iv(texturesUniformLoc, static_cast<GLsizei>(textureUnits.size()), textureUnits.data());
        
        GLenum err = glGetError();
        if (err != GL_NO_ERROR)
            std::cout << "glUniform1iv failed with error: " << err << std::endl;
        else
            std::cout << "glUniform1iv succeeded!" << std::endl;
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

    rebindTextures(); //TODO: all instances sharing texture now

   for (auto& VAOGroup : VAOGroups)
   {
        VAOGroup->drawGroup(shaderInstance, windowInstance);
   }
}

}

#endif


