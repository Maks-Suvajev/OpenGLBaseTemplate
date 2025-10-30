#include "TextureLoader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>

namespace gfx {


    GLuint loadTexture(const std::filesystem::path& texturePath)
    {
        GLuint textureID;
        GLenum textureFormat;

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

        if (nrChannels == 3)
        {
            textureFormat = GL_RGB;
        }
        else if (nrChannels == 4)
        {
            textureFormat = GL_RGBA;

        }
        else
        {
            textureFormat = GL_RGB;
        }

        #ifdef ENABLE_DEBUG_MESSAGES
            std::cout << "DEBUG::Number of channels detected = " << nrChannels << std::endl;
        #endif

        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, textureFormat, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            glDeleteTextures(1, &textureID);

            #ifdef ENABLE_DEBUG_MESSAGES
                std::cout << "ERROR::Failed to load texture!" << std::endl;
            #endif

            return 0;
        }

        stbi_image_free(data);

        return textureID;
    }




















};