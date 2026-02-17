#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{

    QWidget* centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);

    QVBoxLayout* layout = new QVBoxLayout(centralWidget);

    QLabel* label = new QLabel("Engine Control Panel", this);
    layout->addWidget(label);

    m_viewport = std::make_unique<Viewport>();

    layout->addWidget(m_viewport.get());

    int index = layout->indexOf(m_viewport.get());
    layout->setStretch(index, 1);


    QPushButton* button = new QPushButton();
    layout->addWidget(button);


    connect(button, &QPushButton::clicked, this, &MainWindow::handleButtonClick);

    this->setWindowTitle("Rendering Engine");
    this->resize(1280, 720);
}

void MainWindow::handleButtonClick()
{
    std::cout << "Button was clicked!!" << std::endl;
}