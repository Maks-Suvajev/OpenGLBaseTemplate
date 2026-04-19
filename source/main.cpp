#include <QApplication>
#include "EngineCore.h"
#include "MainWindow.h"



int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    gui::MainWindow w;
    w.show();

    return app.exec();
}