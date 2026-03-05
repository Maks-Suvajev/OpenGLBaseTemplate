#include "EngineCore.h"

#include <QApplication>
#include "MainWindow.h"
#include "EngineCore.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    MainWindow w;
    w.show();

    return app.exec();
}