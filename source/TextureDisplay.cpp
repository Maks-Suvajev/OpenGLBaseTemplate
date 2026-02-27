#include "TextureDisplay.h"


TextureDisplay::TextureDisplay(gfx::TextureManager* textureManager, QWidget* parent)
    : QWidget(parent)
{
    m_mainLayout = std::make_unique<QVBoxLayout>(this);

    QLabel* title = new QLabel("Texture Loader");
    title->setAlignment(Qt::AlignCenter);

    QFont font = title->font();
    font.setPointSize(15);
    title->setFont(font);
    
    m_mainLayout->addWidget(title);
    m_mainLayout->setAlignment(Qt::AlignLeft);

    // this->setFixedHeight(200);
     //this->setFixedWidth(400);

    m_managerViewWithButton = std::make_unique<QVBoxLayout>();

    m_managerView = std::make_unique<QListView>(this);
    m_model = std::make_unique<TextureModel>(textureManager, this);

    m_managerView->setModel(m_model.get());
    m_managerView->setMouseTracking(true);
    m_managerView->setSelectionMode(QAbstractItemView::ExtendedSelection);

    m_managerViewWithButton->addWidget(m_managerView.get(), 1);
    addCurrDirectoryDisplay();
    addChangeDirectoryButton();

    QHBoxLayout* main_panel = new QHBoxLayout();

    createButtonPanel();

    main_panel->addLayout(m_managerViewWithButton.get());
    main_panel->addLayout(m_buttonPanel.get());

    m_mainLayout->addLayout(main_panel);
}

void TextureDisplay::addCurrDirectoryDisplay()
{
    QHBoxLayout* layout = new QHBoxLayout();

    m_currentDirectory = QString::fromStdString(m_model->getCurrentTextureDirectory().string());

    QLabel* titleLabel = new QLabel("Current directory: ");
    m_displayLabel = new QLabel(m_currentDirectory); 

    layout->addWidget(titleLabel);
    layout->addWidget(m_displayLabel);

    layout->setSpacing(5);
    layout->addStretch(1);

    m_managerViewWithButton->addLayout(layout);
}

void TextureDisplay::setButtonColours(QWidget* widget)
{
    QPalette palette = widget->palette();

    palette.setColor(QPalette::Window, backgroundColour);
    palette.setColor(QPalette::Base, backgroundColour);
    palette.setColor(QPalette::Button, buttonColour);

    widget->setPalette(palette);
    widget->setAutoFillBackground(true);
}

void TextureDisplay::addChangeDirectoryButton()
{
    QPushButton* button = new QPushButton("Change active directory...");
    setButtonColours(button);
    button->setText("Change active directory...");
    connect(button, &QPushButton::clicked, this, &TextureDisplay::changeDirectoryPressed);
    m_managerViewWithButton->addWidget(button);
}

template<typename FuncType>
void TextureDisplay::addButtonToPanel(QString label, FuncType function)
{
    QPushButton* button = new QPushButton(label);
    setButtonColours(button);
    button->setText(label);
    connect(button, &QPushButton::clicked, this, function);
    m_buttonPanel->addWidget(button);
}

void TextureDisplay::createButtonPanel()
{
    m_buttonPanel = std::make_unique<QVBoxLayout>();
    m_buttonPanel->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    m_buttonPanel->setSpacing(0);
    m_buttonPanel->setContentsMargins(0,0,0,0);

    addButtonToPanel("REFRESH", &TextureDisplay::refreshPressed);
    addButtonToPanel("LOAD", &TextureDisplay::loadTexturePressed);
    addButtonToPanel("LOAD ALL", &TextureDisplay::loadAllTexturesPressed);
    addButtonToPanel("UNLOAD", &TextureDisplay::unloadTexturePressed);
    addButtonToPanel("UNLOAD ALL", &TextureDisplay::unloadAllTexturesPressed);

}

void TextureDisplay::refreshPressed()
{
    m_model->refreshTextures();
}

void TextureDisplay::loadTexturePressed()
{
    QModelIndexList selectedIndices = m_managerView->selectionModel()->selectedIndexes();

    for (const auto& index : selectedIndices)
    {
        QString name = index.data(Qt::DisplayRole).toString();
        m_model->loadTexture(name.toStdString());
        emit m_model->dataChanged(index, index);
    }

}

void TextureDisplay::loadAllTexturesPressed()
{
    for (int i = 0; i < m_managerView->model()->rowCount(); ++i) // Not sure if there's better way to iterate..
    {
        QModelIndex index = m_managerView->model()->index(i, 0);
        QString name = index.data(Qt::DisplayRole).toString();
        m_model->loadTexture(name.toStdString());
        emit m_model->dataChanged(index, index);
    }
}

void TextureDisplay::unloadTexturePressed()
{
    QModelIndexList selectedIndices = m_managerView->selectionModel()->selectedIndexes();

    for (const auto& index : selectedIndices)
    {
        QString name = index.data(Qt::DisplayRole).toString();
        m_model->unloadTexture(name.toStdString());
        emit m_model->dataChanged(index, index);
    }
}

void TextureDisplay::unloadAllTexturesPressed()
{
    for (int i = 0; i < m_managerView->model()->rowCount(); ++i) // Not sure if there's better way to iterate..
    {
        QModelIndex index = m_managerView->model()->index(i, 0);
        QString name = index.data(Qt::DisplayRole).toString();
        m_model->unloadTexture(name.toStdString());
        emit m_model->dataChanged(index, index);
    }
}

void TextureDisplay::changeDirectoryPressed()
{
    std::filesystem::path currFolder = m_model->getCurrentTextureDirectory();

    QString directory = QFileDialog::getExistingDirectory(this, "New Texture Directory", QString::fromStdString(currFolder.string()));

    m_model->updateTexturePath(directory.toStdString());

    if (currFolder.string() != directory.toStdString())
    {
        m_currentDirectory = directory;
        m_displayLabel->setText(m_currentDirectory);
    }
}