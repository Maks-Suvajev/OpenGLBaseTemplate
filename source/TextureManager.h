#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H


#include <glad/glad.h>
#include <filesystem>
#include <unordered_map>
#include <vector>
#include <string>
#include <memory>


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

class TextureManager
{
    public:
        TextureManager(std::vector<std::filesystem::path> texturePaths);
        Texture loadTexture(const std::filesystem::path& texturePath, std::string name);
        std::string extractTextureName(std::filesystem::path texturePath);
        GLuint getTexture(std::string name);
        void printAllTextures();



    private:
        std::unordered_map<std::string, std::unique_ptr<Texture>> loadedTextures;



};


}

#endif