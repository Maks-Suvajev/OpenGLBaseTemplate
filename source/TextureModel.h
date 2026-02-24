#ifndef TEXTURE_MODEL_H
#define TEXTURE_MODEL_H

#include <QBrush>
#include <QColor>

#include <QObject>
#include <QAbstractListModel>

#include "TextureManager.h"


/*  TextureRole is a reflection of the Texture struct found within the TextureManager
struct Texture
{
    GLuint textureID = INVALID_TEXTURE_ID;
    GLenum textureFormat = INVALID_TEXTURE_FORMAT;
    int width = 0;
    int height = 0;
    int nrChannels = 0;
    std::filesystem::path systemSourcePath;
};
*/

class TextureModel : public QAbstractListModel
{
    Q_OBJECT
    
    public:
        explicit TextureModel(gfx::TextureManager* manager, QObject* parent);

        //QT interface
        int rowCount(const QModelIndex &parent = QModelIndex()) const override;
        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

        // Button functions
        void refreshTextures();
        void loadTexture(std::string name);
        void unloadTexture(std::string name);
        
        enum TextureRole
        {
            NameRole          = Qt::DisplayRole,
            TextureIDRole     = Qt::UserRole + 1,
            TextureFormatRole = Qt::UserRole + 2,
            WidthRole         = Qt::UserRole + 3,
            HeightRole        = Qt::UserRole + 4,
            NrChannelsRole    = Qt::UserRole + 5,
            FilePathRole      = Qt::UserRole + 6,
            LoadedRole        = Qt::UserRole + 7
        };
        
    private:
        void subscribeToTextureUpdates();
        QString decodeTextureFormat(GLenum textureFormat) const;
        QString formatToolTip(std::string key, gfx::Texture* texture) const;
        QBrush colourBackground(gfx::Texture* texture) const;

        gfx::TextureManager*        m_manager;
        std::vector<std::string>    m_activeTextureKeys; 
};


#endif