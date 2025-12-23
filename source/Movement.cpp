#include "Movement.h"

namespace gfx
{

void Movement::performTestAnimation(std::deque<gfx::Transform> &objects)
{

    uint32_t counter = 0;

    for (auto& object : objects)
    {
        float angle = 20.0f * counter;
        counter++;

        object.rotation.x = 1.0f * angle;
        object.rotation.y = 0.3f * angle;
        object.rotation.z = 0.5f * angle;
        
        
        if (counter % 2 == 0)
            object.rotation.x = 1.0f * angle * glm::sin(static_cast<float>(glfwGetTime()) * 0.2f);

        if (counter % 3 == 0)
            object.rotation.y = 0.3f * angle * glm::sin(static_cast<float>(glfwGetTime()) * 0.2f);

    }

}

}