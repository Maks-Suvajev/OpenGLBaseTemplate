#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

// STL
#include <filesystem>
#include <unordered_map>
#include <vector>
#include <string>
#include <memory>
#include <optional>
#include <iostream>

//  OpenGL
#include <qopengl.h>
#include <QOpenGLExtraFunctions>

// QT signals access
#include <QObject>

#include "TextureTypes.h"

// Asset manager
#include "GfxAssetsManager.h"

namespace gfx 
{

class TextureManager : public QObject
{
    Q_OBJECT

    signals:
        void texturesUpdated();

    public:
        TextureManager(GfxAssetsManager* assetsManager, QOpenGLExtraFunctions* openGLFunctions );
        void registerTexture(const std::filesystem::path& texturePath, std::string name);
        void registerAllTextures();
        void loadTexture(std::string name);
        void loadAllTextures();
        std::string extractTextureName(std::filesystem::path texturePath);
        GLuint getTextureID(std::string name);
        void printAllTextures();
        const std::unordered_map<std::string, std::unique_ptr<Texture>>& getMap();

    private:
        std::unordered_map<std::string, std::unique_ptr<Texture>> m_textures;
        QOpenGLExtraFunctions* m_openGLFunctions;
        GfxAssetsManager* m_assetsManager;

};


}

#endif