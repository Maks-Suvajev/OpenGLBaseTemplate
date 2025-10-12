
#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Camera.h"

namespace gfx {

class Window
{

    public:
        Window(const char * projectName);

        void processKeyboardInput();

        Camera * getCameraInstance()
        {
            return camera;
        }

        void setScreenClearColour(glm::vec4 colour)
        {
            if (colour != screenClearColour)
            {
                screenClearColour = colour;
                glClearColor(screenClearColour.r, screenClearColour.g, screenClearColour.b, screenClearColour.a);
            }
        }

        void clearScreen()
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }

        GLFWwindow * getGlfwWindow()
        {
            return glfwWindow;
        }

    private:
        GLFWwindow* glfwWindow;
        Camera * camera;
        ScreenResolution resolution;
        glm::vec4 screenClearColour;

    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
    static void mouseCallback(GLFWwindow* window, double xPosition, double yPosition);
    static void scrollCallback(GLFWwindow* window, double xOffset, double yOffSet);


};
 
}

#endif