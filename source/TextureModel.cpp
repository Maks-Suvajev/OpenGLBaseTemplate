#include "TextureModel.h"

TextureModel::TextureModel(gfx::TextureManager* manager, QObject* parent)
    : QAbstractListModel(parent),
      m_manager(manager)
{
    updateLoadedTextures();
    subscribeToTextureUpdates();
}


void TextureModel::subscribeToTextureUpdates()
{
    const auto reload = [this]() {
        beginResetModel();
        updateLoadedTextures();
        endResetModel();
    };

    connect(m_manager, &gfx::TextureManager::texturesUpdated, this, reload);
}


void TextureModel::updateLoadedTextures()
{
    std::vector<std::string> currActiveTextures;

    for (const auto& [key, texture] : m_manager->getMap())
    {
        currActiveTextures.push_back(key);
    }

    m_activeTextureKeys = currActiveTextures;
}

int TextureModel::rowCount(const QModelIndex &parent) const
{
    return m_activeTextureKeys.size();
}

QString TextureModel::decodeTextureFormat(GLenum textureFormat) const
{
    switch(textureFormat)
    {
        case GL_RED:
            return QString("GL_RED");
            break;

        case GL_GREEN:
            return QString("GL_GREEN");
            break;

        case GL_BLUE:
            return QString("GL_BLUE");
            break;

        case GL_ALPHA:
            return QString("GL_ALPHA");
            break;

        case GL_RGB:
            return QString("GL_RGB");
            break;

        case GL_RGBA:
            return QString("GL_RGBA");
            break;
        
        default:
            return QString("INVALID FORMAT");
    }
}

QString TextureModel::formatToolTip(std::string key, gfx::Texture* texture) const
{
    return QString(
        "<b>Name:</b> %1<br>"
        "<b>Texture ID:</b> %2<br>"
        "<b>Texture Format:</b> %3<br>"
        "<b>Resolution:</b> %4x%5<br>"
        "<b>Number of channels:</b> %6<br>"
        "<b>Filepath:</b> %7<br>"
    ).arg(key)
    .arg(texture->textureID)
    .arg(decodeTextureFormat(texture->textureFormat))
    .arg(texture->width)
    .arg(texture->height)
    .arg(texture->nrChannels)
    .arg(texture->systemSourcePath.string());
}

QBrush TextureModel::colourBackground(gfx::Texture* texture) const
{
    if (texture->isLoaded)
    {
        return QBrush(QColor(0x3E, 0xD6, 0x6E)); // Green
    }
    else
    {
        return QBrush(QColor(0xD6, 0x55, 0x3E)); // Red
    }
}

QVariant TextureModel::data(const QModelIndex &index, int role) const
{ 
    if (!index.isValid() || m_manager == nullptr)
    {
        return QVariant();
    }

    auto key = m_activeTextureKeys[index.row()];

    const auto& texture = m_manager->getMap().at(key);
    
    switch (role)
    {
        case Qt::BackgroundRole:
            return colourBackground(texture.get());

        case Qt::ToolTipRole:
            return formatToolTip(key, texture.get());

        case NameRole:    
            return QString::fromStdString(key);                                             

        case TextureIDRole:
            return texture->textureID;

        case TextureFormatRole:
            return texture->textureFormat;

        case WidthRole:
            return texture->width;

        case HeightRole:
            return texture->height;

        case NrChannelsRole:
            return texture->nrChannels;

        case FilePathRole:
            return QString::fromStdString(texture->systemSourcePath.generic_string());

        case LoadedRole:
            return true; // currently only displaying loaded textures

        default:
            return QVariant();
    }

    return QVariant();
}
