#include "TextureManager.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>

namespace gfx {

TextureManager::TextureManager(std::vector<std::filesystem::path> texturePaths)
{
    for (const auto& texturePath : texturePaths)
    {
        std::string textureName = extractTextureName(texturePath);

        Texture loadedTexture = loadTexture(texturePath, textureName);

        if (loadedTexture.textureID != INVALID_TEXTURE_ID)
        {
            loadedTextures[textureName] = std::make_unique<Texture>(std::move(loadedTexture));
        }
    }
}

std::string TextureManager::extractTextureName(std::filesystem::path texturePath)
{
    return texturePath.filename().string();
}

void TextureManager::printAllTextures()
{
    std::cout << "----------------------------------------------------------------------------" << std::endl;

    std::cout << "| ----- Printing currently available textures and their source paths ----- |" << std::endl;

    for (auto& [key, item] : loadedTextures)
    {
        std::cout << "----------------------------------------------------------------------------" << std::endl;
        std::cout << "Key: " << key << std::endl;

        if (item)
        {
            std::cout << "Path: " << item->systemSourcePath.string() << std::endl;
        }
        else
        {
            std::cout << "Path: NULLPTR" << std::endl;
        }        
    }

    std::cout << "----------------------------------------------------------------------------" << std::endl << std::endl;
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

    #ifdef ENABLE_DEBUG_MESSAGES
        std::cout << "DEBUG::Successfully loaded texture with key: " << name << std::endl;
    #endif

    return textureData;
}

GLuint TextureManager::getTexture(std::string name)
{
    auto it = loadedTextures.find(name);

    // Check if key exists, also check if unique_ptr is valid that it points to
    if (it == loadedTextures.end() || !it->second) 
    {
        #ifdef ENABLE_DEBUG_MESSAGES
            std::cout << "ERROR::Invalid key given: " << name << std::endl;
        #endif

        return INVALID_TEXTURE_ID;
    }

    #ifdef ENABLE_DEBUG_MESSAGES
        std::cout << "DEBUG::Key: " << name << " Texture ID Found: " << loadedTextures[name]->textureID << std::endl;
    #endif


    return loadedTextures[name]->textureID;
}

};