#include "TextureDisplay.h"


TextureDisplay::TextureDisplay(gfx::TextureManager* textureManager, QWidget* parent)
    : QWidget(parent)
{
    m_mainLayout = std::make_unique<QVBoxLayout>(this);

    this->setFixedHeight(200);
    this->setFixedWidth(500);


    m_view = std::make_unique<QListView>(this);
    m_model = std::make_unique<TextureModel>(textureManager, this);

    m_view->setModel(m_model.get());
    m_mainLayout->addWidget(m_view.get(), 1);

    m_view->setMouseTracking(true);
}

void TextureDisplay::setPanelInteractability()
{
    m_detailsLabel->setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::TextSelectableByKeyboard);
}
