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

    QLabel* titleLabel = new QLabel("Active directory: ");
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
    QPushButton* changeDirButton = new QPushButton("Change active directory");
    setButtonColours(changeDirButton);
    changeDirButton->setText("Change active directory");
    connect(changeDirButton, &QPushButton::clicked, this, &TextureDisplay::changeDirectoryPressed);

    QPushButton* openExplorerButton = new QPushButton("Open file explorer");
    setButtonColours(openExplorerButton);
    openExplorerButton->setText("Open Explorer");
    connect(openExplorerButton, &QPushButton::clicked, this, &TextureDisplay::openExplorerPressed);

    QHBoxLayout* buttonLayout = new QHBoxLayout(); 

    buttonLayout->addWidget(changeDirButton);
    buttonLayout->addWidget(openExplorerButton);

    m_managerViewWithButton->addLayout(buttonLayout);
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

    addButtonToPanel("Refresh", &TextureDisplay::refreshPressed);
    addButtonToPanel("Load", &TextureDisplay::loadTexturePressed);
    addButtonToPanel("Load All", &TextureDisplay::loadAllTexturesPressed);
    addButtonToPanel("Unload", &TextureDisplay::unloadTexturePressed);
    addButtonToPanel("Unload All", &TextureDisplay::unloadAllTexturesPressed);

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
        QString key = index.data(TextureModel::FilePathRole).toString();
        m_model->loadTexture(key.toStdString());
        emit m_model->dataChanged(index, index);
    }

}

void TextureDisplay::loadAllTexturesPressed()
{
    for (int i = 0; i < m_managerView->model()->rowCount(); ++i) // Not sure if there's better way to iterate..
    {
        QModelIndex index = m_managerView->model()->index(i, 0);
        QString key = index.data(TextureModel::FilePathRole).toString();
        m_model->loadTexture(key.toStdString());
        emit m_model->dataChanged(index, index);
    }
}

void TextureDisplay::unloadTexturePressed()
{
    QModelIndexList selectedIndices = m_managerView->selectionModel()->selectedIndexes();

    for (const auto& index : selectedIndices)
    {
        QString key = index.data(TextureModel::FilePathRole).toString();
        m_model->unloadTexture(key.toStdString());
        emit m_model->dataChanged(index, index);
    }
}

void TextureDisplay::unloadAllTexturesPressed()
{
    for (int i = 0; i < m_managerView->model()->rowCount(); ++i) // Not sure if there's better way to iterate..
    {
        QModelIndex index = m_managerView->model()->index(i, 0);
        QString key = index.data(TextureModel::FilePathRole).toString();
        m_model->unloadTexture(key.toStdString());
        emit m_model->dataChanged(index, index);
    }
}

void TextureDisplay::changeDirectoryPressed()
{
    std::filesystem::path currFolder = m_model->getCurrentTextureDirectory();

    QString directory = QFileDialog::getExistingDirectory(this, "New Texture Directory", QString::fromStdString(currFolder.string()));

    if (directory.isEmpty())
    {
        return;
    }

    m_model->updateTexturePath(directory.toStdString());

    if (currFolder.string() != directory.toStdString())
    {
        m_currentDirectory = directory;
        m_displayLabel->setText(m_currentDirectory);
    }
}

void TextureDisplay::openExplorerPressed()
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(m_currentDirectory));
}