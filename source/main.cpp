#include "Game.h"

#include <glm/glm.hpp>


int main()
{

    #ifdef ENABLE_DEBUG_MESSAGES
        std::cout << "Debug messages activated!" << std::endl;
    #endif

    std::unique_ptr<Game<glm::vec3>> GameInstance = std::make_unique<Game<glm::vec3>>();

    GameInstance->runLoop();

	return 0;

}