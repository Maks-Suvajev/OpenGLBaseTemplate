#ifndef TEXTURE_DISPLAY_H
#define TEXTURE_DISPLAY_H

#include <QWidget>
#include <QListView>
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>

#include "TextureModel.h"
#include "TextureManager.h"



class TextureDisplay : public QWidget
{
    Q_OBJECT

    public:
        explicit TextureDisplay(gfx::TextureManager* textureManager, QWidget* parent = nullptr);

    private:
        void setPanelInteractability();

        std::unique_ptr<QVBoxLayout>    m_mainLayout;
        std::unique_ptr<QLabel>         m_detailsLabel;
        std::unique_ptr<QListView>      m_view;
        std::unique_ptr<TextureModel>   m_model;

};


#endif