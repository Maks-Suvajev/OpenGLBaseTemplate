#include "TextureDisplay.h"


TextureDisplay::TextureDisplay(gfx::TextureManager* textureManager, QWidget* parent)
    : QWidget(parent)
{
    m_mainLayout = std::make_unique<QHBoxLayout>(this);

    this->setFixedHeight(200);
    this->setFixedWidth(500);

    m_view = std::make_unique<QListView>(this);
    m_model = std::make_unique<TextureModel>(textureManager, this);

    m_view->setModel(m_model.get());
    m_mainLayout->addWidget(m_view.get(), 1);

    createButtonPanel();
    m_mainLayout->addLayout(m_buttonGridLayout.get());

    m_view->setMouseTracking(true);
}

void TextureDisplay::createButtonPanel()
{
    m_buttonGridLayout = std::make_unique<QGridLayout>();
    m_buttonGridLayout->setAlignment(Qt::AlignTop);

    QPushButton* refreshButton = new QPushButton("Refresh");
    refreshButton->setText("Refresh");
    connect(refreshButton, &QPushButton::clicked, this, &TextureDisplay::refreshPressed);
    m_buttonGridLayout->addWidget(refreshButton, 0, 0);

    QPushButton* loadButton = new QPushButton("Load");
    loadButton->setText("Load Texture");
    connect(loadButton, &QPushButton::clicked, this, &TextureDisplay::loadTexturePressed);
    m_buttonGridLayout->addWidget(loadButton, 0, 1);

    QPushButton* unloadButton = new QPushButton("Unload");
    unloadButton->setText("Unload Texture");
    connect(unloadButton, &QPushButton::clicked, this, &TextureDisplay::unloadTexturePressed);
    m_buttonGridLayout->addWidget(unloadButton, 1, 0);

    QPushButton* dummyButton = new QPushButton("Dummy");
    dummyButton->setText("Dummy");
    connect(dummyButton, &QPushButton::clicked, this, &TextureDisplay::dummyButtonPressed);
    m_buttonGridLayout->addWidget(dummyButton, 1, 1);

}

void TextureDisplay::refreshPressed()
{
    m_model->refreshTextures();
}

void TextureDisplay::loadTexturePressed()
{
    m_model->loadTexture("test");
}

void TextureDisplay::unloadTexturePressed()
{
    m_model->unloadTexture("test");
}

void TextureDisplay::dummyButtonPressed()
{
    std::cout << "Dummy button pressed!!" << std::endl;
}