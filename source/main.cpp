#include "EngineCore.h"

#include <glm/glm.hpp>


int main()
{

    #ifdef ENABLE_DEBUG_MESSAGES
        std::cout << "Debug messages activated!" << std::endl;
    #endif

    std::unique_ptr<EngineCore<glm::vec3>> engineInstance = std::make_unique<EngineCore<glm::vec3>>();

    engineInstance->runLoop();

	return 0;

}