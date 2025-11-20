#include "Window.h"


namespace gfx {

//const glm::vec4 initialScreenClearColour = glm::vec4(0.2f, 0.3f, 0.3f, 1.0f);
const glm::vec4 initialScreenClearColour = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);


Window::Window(const char * projectName)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindow = glfwCreateWindow(windowInitialWidth, windowInitialHeight, projectName, NULL, NULL);

    if (glfwWindow == NULL)
    {
        #ifdef ENABLE_DEBUG_MESSAGES
            std::cout << "ERROR::Failed to create a GLFW window!" << std::endl;
        #endif

        glfwTerminate();
    }
    else
    {
        #ifdef ENABLE_DEBUG_MESSAGES
            std::cout << "DEBUG::Successfully created a GLFW window!" << std::endl;
        #endif
    }

    glfwMakeContextCurrent(glfwWindow);

	glfwSetWindowUserPointer(glfwWindow, this); // Store pointer to Window object to access later in static callback functions

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        #ifdef ENABLE_DEBUG_MESSAGES
            std::cout << "ERROR::Failed to initialize GLAD GL function loader!" << std::endl;
        #endif
    } 

    glViewport(0, 0, windowInitialWidth, windowInitialHeight);

	glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    //Setup callbacks
	glfwSetFramebufferSizeCallback(glfwWindow, framebufferSizeCallback);
	glfwSetCursorPosCallback(glfwWindow, mouseCallback);
	glfwSetScrollCallback(glfwWindow, scrollCallback);

    setScreenClearColour(initialScreenClearColour);

    glEnable(GL_DEPTH_TEST);

	camera = new Camera(windowInitialWidth, windowInitialHeight);
};

void Window::framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	Window * windowInstance = static_cast<Window*>(glfwGetWindowUserPointer(window));
	windowInstance->camera->updateScreenResolution(static_cast<float>(width),static_cast<float>(height));
	glViewport(0, 0, width, height);
}

void Window::processKeyboardInput()
{
	camera->processKeyboardInput(glfwWindow);	
}

void Window::mouseCallback(GLFWwindow* window, double xPosition, double yPosition)
{
	Window * windowInstance = static_cast<Window*>(glfwGetWindowUserPointer(window));
	windowInstance->camera->processMouseInput(xPosition, yPosition);
}


void Window::scrollCallback(GLFWwindow* window, double xOffset, double yOffSet)
{
	Window * windowInstance = static_cast<Window*>(glfwGetWindowUserPointer(window));
	windowInstance->camera->processScrollInput(xOffset, yOffSet);
}

}







