#include "TextureManager.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>

namespace gfx {

TextureManager::TextureManager(std::vector<TextureToLoad> texturesToLoad)
{
    for (const auto& textureToLoad : texturesToLoad)
    {
        Texture loadedTexture = loadTexture(textureToLoad.texturePath, textureToLoad.name);

        if (loadedTexture.textureID != INVALID_TEXTURE_ID)
        {
            loadedTextures[textureToLoad.name] = std::make_unique<Texture>(std::move(loadedTexture));
        }
    }
}


// Using name as hash, user can load the same texture under different names if they want
Texture TextureManager::loadTexture(const std::filesystem::path& texturePath, std::string name)
{
    Texture textureData{};

    if (loadedTextures.contains(name))
    {
        #ifdef ENABLE_DEBUG_MESSAGES
            std::cout << "DEBUG::Texture already loaded with the key: " << name << std::endl;
            std::cout << "DEBUG::Returning empty struct" << std::endl;
        #endif

        return textureData;
    }

    GLuint textureID;
    GLenum textureFormat;
    GLenum internalFormat; // GPU side format 8-bit vs 16-bit pixel precision. 

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // Set the texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Load image into texture 1 using STB library
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);

    #ifdef ENABLE_DEBUG_MESSAGES
        std::cout << "DEBUG::Loading texture path: " << texturePath.string() << std::endl;
    #endif

    unsigned char* data = stbi_load(texturePath.string().c_str(), &width, &height, &nrChannels, 0);

    // Assign GL texture format
    // Using stbi load with 8 bit depth so default to that for internal format for now.
    switch(nrChannels)
    {
        case 1:
            textureFormat = GL_RED;
            internalFormat = GL_R8;
            break;

        case 2:
            textureFormat = GL_RG;
            internalFormat = GL_RG8;
            break;

        case 3:
            textureFormat = GL_RGB;
            internalFormat = GL_RGB8;
            break;

        case 4:
            textureFormat = GL_RGBA;
            internalFormat = GL_RGBA8;
            break;

        default:
            textureFormat = INVALID_TEXTURE_FORMAT;
            internalFormat = INVALID_TEXTURE_FORMAT;
            break;
    }

    #ifdef ENABLE_DEBUG_MESSAGES
        std::cout << "DEBUG::Number of channels detected = " << nrChannels << std::endl;
    #endif

    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, textureFormat, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        textureData.textureID = textureID;
        textureData.textureFormat = textureFormat;
        textureData.systemSourcePath = texturePath;
        textureData.width = width;
        textureData.height = height;
        textureData.nrChannels = nrChannels;

        stbi_image_free(data);
    }
    else
    {
        glDeleteTextures(1, &textureID);

        #ifdef ENABLE_DEBUG_MESSAGES
            std::cout << "ERROR::Failed to load texture!" << std::endl;
        #endif

        stbi_image_free(data);

    }

    return textureData;
}




















};