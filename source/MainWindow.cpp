#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{

    QWidget* centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);

    QVBoxLayout* layout = new QVBoxLayout(centralWidget);

    QLabel* label = new QLabel("Engine Control Panel", this);
    layout->addWidget(label);

    QPushButton* button = new QPushButton();
    layout->addWidget(button);

    connect(button, &QPushButton::clicked, this, &MainWindow::handleButtonClick);

    this->setWindowTitle("Rendering Engine");
    this->resize(300, 200);
}

void MainWindow::handleButtonClick()
{
    std::cout << "Button was clicked!!" << std::endl;
}