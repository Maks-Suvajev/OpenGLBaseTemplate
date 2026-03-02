#ifndef TEXTURE_TYPES_H
#define TEXTURE_TYPES_H

#include <filesystem>
#include <qopengl.h>

namespace gfx
{

constexpr GLenum INVALID_TEXTURE_FORMAT = 0;
constexpr GLenum INVALID_TEXTURE_ID = 0;

struct TextureConfig
{
    GLenum textureType = GL_TEXTURE_2D;
    GLenum wrapParam_S = GL_CLAMP_TO_EDGE;
    GLenum wrapParam_T = GL_CLAMP_TO_EDGE;
    GLenum minFilter   = GL_LINEAR;
    GLenum magFilter   = GL_LINEAR;
    bool flipOnLoad    = true;
};

struct Texture
{
    std::string name;
    GLuint textureID     = INVALID_TEXTURE_ID;
    GLenum textureFormat = INVALID_TEXTURE_FORMAT;
    int width            = 0;
    int height           = 0;
    int nrChannels       = 0;
    bool isLoaded        = false;
    bool loadError       = false;
    std::filesystem::path systemSourcePath;
    TextureConfig config;
};

}
#endif
