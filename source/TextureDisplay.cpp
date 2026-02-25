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
    m_view->setSelectionMode(QAbstractItemView::ExtendedSelection);
}

void TextureDisplay::createButtonPanel()
{
    m_buttonGridLayout = std::make_unique<QGridLayout>();
    m_buttonGridLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    m_buttonGridLayout->setSpacing(0);
    m_buttonGridLayout->setContentsMargins(0,0,0,0);

    QPushButton* refreshButton = new QPushButton("REFRESH");
    refreshButton->setText("REFRESH");
    //refreshButton->setFixedSize(100, 100); // TODO: Make a class derived from QPushButton to automate button shape (and styling)
    connect(refreshButton, &QPushButton::clicked, this, &TextureDisplay::refreshPressed);
    m_buttonGridLayout->addWidget(refreshButton, 0, 0);

    QPushButton* loadButton = new QPushButton("LOAD");
    loadButton->setText("LOAD");
    //loadButton->setFixedSize(100, 100);
    connect(loadButton, &QPushButton::clicked, this, &TextureDisplay::loadTexturePressed);
    m_buttonGridLayout->addWidget(loadButton, 0, 1);

    QPushButton* unloadButton = new QPushButton("UNLOAD");
    unloadButton->setText("UNLOAD");
    //unloadButton->setFixedSize(100, 100);
    connect(unloadButton, &QPushButton::clicked, this, &TextureDisplay::unloadTexturePressed);
    m_buttonGridLayout->addWidget(unloadButton, 1, 0);

    QPushButton* dummyButton = new QPushButton("DUMMY");
    dummyButton->setText("DUMMY");
    //dummyButton->setFixedSize(100, 100);
    connect(dummyButton, &QPushButton::clicked, this, &TextureDisplay::dummyButtonPressed);
    m_buttonGridLayout->addWidget(dummyButton, 1, 1);

}

void TextureDisplay::refreshPressed()
{
    m_model->refreshTextures();
}

void TextureDisplay::loadTexturePressed()
{
    QModelIndexList selectedIndices = m_view->selectionModel()->selectedIndexes();

    for (const auto& index : selectedIndices)
    {
        QString name = index.data(Qt::DisplayRole).toString();
        m_model->loadTexture(name.toStdString());
        emit m_model->dataChanged(index, index);
    }

}

void TextureDisplay::unloadTexturePressed()
{
    QModelIndexList selectedIndices = m_view->selectionModel()->selectedIndexes();

    for (const auto& index : selectedIndices)
    {
        QString name = index.data(Qt::DisplayRole).toString();
        m_model->unloadTexture(name.toStdString());
        emit m_model->dataChanged(index, index);
    }


}

void TextureDisplay::dummyButtonPressed()
{
    std::cout << "Dummy button pressed!!" << std::endl;
}