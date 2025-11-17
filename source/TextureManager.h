#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H


#include <glad/glad.h>
#include <filesystem>
#include <unordered_map>


namespace gfx 
{

constexpr GLenum INVALID_TEXTURE_FORMAT = 0;
constexpr GLenum INVALID_TEXTURE_ID = 0;

struct Texture
{
    GLuint textureID = INVALID_TEXTURE_ID;
    GLenum textureFormat = INVALID_TEXTURE_FORMAT;
    int width = 0;
    int height = 0;
    int nrChannels = 0;
    std::filesystem::path systemSourcePath;
};

struct TextureToLoad
{
    std::filesystem::path texturePath;
    std::string name;
};

class TextureManager
{
    public:
        TextureManager(std::vector<TextureToLoad> texturesToLoad);
        Texture loadTexture(const std::filesystem::path& texturePath, std::string name);



    private:
        std::unordered_map<std::string, std::unique_ptr<Texture>> loadedTextures;



};


}

#endif