#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <vector>
#include <glm/glm.hpp>
#include "RenderObject.h"

namespace gfx
{

template<typename T>
class Movement
{
    public:
        Movement(std::vector<std::shared_ptr<RenderObject<T>>> objects);
        void performTestAnimation();
        void initMovableObjects(std::vector<std::shared_ptr<RenderObject<T>>> objects);
        void addNewObject(std::shared_ptr<RenderObject<T>> newObject);
        void removeObject(std::shared_ptr<RenderObject<T>> object);


    private:
        void printPositionsOfRegisteredObjects();
        std::vector<std::shared_ptr<RenderObject<T>>> movableObjects;

};

template<typename T>
Movement<T>::Movement(std::vector<std::shared_ptr<RenderObject<T>>> objects)
{
    initMovableObjects(objects);

    #ifdef ENABLE_DEBUG_MESSAGES
        std::cout << "DEBUG::Calling printing of registered objects in Movement Module: " << std::endl;
        printPositionsOfRegisteredObjects();
    #endif
}


template<typename T>
void Movement<T>::initMovableObjects(std::vector<std::shared_ptr<RenderObject<T>>> objects)
{
    movableObjects = objects;
} 

template<typename T>
void Movement<T>::addNewObject(std::shared_ptr<RenderObject<T>> newObject)
{
    movableObjects.push_back(newObject);
}

template<typename T>
void Movement<T>::removeObject(std::shared_ptr<RenderObject<T>> object)
{
    auto location = std::find(movableObjects.begin(), movableObjects.end(), object);

    if (location != movableObjects.end())
    {
        movableObjects.erase(location);
    }
}


template<typename T>
void Movement<T>::printPositionsOfRegisteredObjects()
{
    for (auto& object : movableObjects)
    {
        T position = object->getPosition();

        std::cout << "DEBUG::Movement module has an object registered at position: ";

        std::cout << "DEBUG::PosX = " << position.x << " " << "PosY = " << position.y << " " << "PosZ = " << position.z << std::endl;
    }
}


template<typename T>
void Movement<T>::performTestAnimation()
{
    uint16_t index = 0;

    for (auto& object : movableObjects)
    {
        float rotationAngle = 0;

        glm::mat4 model = glm::mat4(1.0f);

        model = glm::translate(model, object->getPosition());

        if (index == 0 || index % 3 == 0)
        {
            rotationAngle = 20.0f * index * static_cast<float>(glfwGetTime());
        }
        else
        {
            rotationAngle = 20.0f * index;
        }

        model = glm::rotate(model, glm::radians(rotationAngle), glm::vec3(1.0f, 0.3f, 0.5f));

        object->updateModelMatrix(model);

        ++index;
    }
}

}


#endif