#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    QWidget* centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);

    m_layout = std::make_unique<QVBoxLayout>(centralWidget);

    m_engine = std::make_unique<EngineCore>();
    m_viewport = std::make_unique<Viewport>(m_engine.get(), this);

    m_layout->addWidget(m_viewport.get());
    int index = m_layout->indexOf(m_viewport.get());
    m_layout->setStretch(index, 1);

    setupTexturemanagerDisplay();

    setWidgetColours(this);
    this->setWindowTitle("Rendering Engine");
    this->resize(1280, 720);
}

void MainWindow::setupTexturemanagerDisplay()
{
    const auto setup = [this](){
        m_textureDisplay = std::make_unique<TextureDisplay>(m_engine->getTextureManager(), this);
        m_layout->addWidget(m_textureDisplay.get());
        m_textureDisplay->show();
    };

    connect(m_engine.get(), &EngineCore::engineInitialised, this, setup);
}


void MainWindow::setWidgetColours(QWidget* widget)
{
    QPalette palette = widget->palette();

    palette.setColor(QPalette::Window, backgroundColour);
    palette.setColor(QPalette::Base, backgroundColour);
    palette.setColor(QPalette::Button, buttonColour);

    widget->setPalette(palette);
    widget->setAutoFillBackground(true);
}