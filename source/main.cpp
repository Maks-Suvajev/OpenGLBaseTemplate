#include "EngineCore.h"

#include <glm/glm.hpp>

#include <QApplication>
#include "MainWindow.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    MainWindow w;
    w.show();

    return app.exec();

    // #ifdef ENABLE_DEBUG_MESSAGES
    //     std::cout << "Debug messages activated!" << std::endl;
    // #endif

    // std::unique_ptr<EngineCore<glm::vec3>> engineInstance = std::make_unique<EngineCore<glm::vec3>>();

    // engineInstance->runLoop();

	// return 0;

}