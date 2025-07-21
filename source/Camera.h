#ifndef CAMERA_H
#define CAMERA_H


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <GLFW/glfw3.h>



namespace gfx {

//TODO: Future inputs for config file
inline constexpr uint16_t windowInitialWidth  = 800; 
inline constexpr uint16_t windowInitialHeight = 600; 

// Will be replaced by input later. -----------------------------------------------

inline const glm::vec3 initialCameraPosition    = glm::vec3(0.0f, 0.0f, 3.0f);
inline const glm::vec3 initialCameraFront       = glm::vec3(0.0f, 0.0f, -1.0f);
inline const glm::vec3 initialCameraUp          = glm::vec3(0.0f, 1.0f, 0.0f);

inline constexpr double initialYaw      = -90.0f;
inline constexpr double initialPitch    = 0.0f;
inline constexpr double initialRoll     = 0.0f;

// Start X and Y mouse position at the centre of the window
inline constexpr double initialPreviousX = windowInitialWidth / 2.0f;
inline constexpr double initialPreviousY = windowInitialHeight / 2.0f;

inline constexpr double initialOffsetX = 0.0f;
inline constexpr double initialOffsetY = 0.0f;

inline constexpr float initialLookSensitivity = 0.1f; 
inline constexpr float initialCameraMoveSpeed = 0.1f; 

inline constexpr float initialZNear = 0.1f; 
inline constexpr float initialZFar  = 100.0f; 

inline constexpr float initialFOV = 45.0f;

inline constexpr double highPitchLimit  = 89.0f;
inline constexpr double lowPitchLimit   = -89.0f;

inline constexpr double highFovLimit  = 45.0f;
inline constexpr double lowFovLimit   = 1.0f;

// End of initial variable values -------------------------------------------------

struct CameraVectors
{
    glm::vec3 cameraPosition;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;
};

struct TiltAngles
{
    double yaw;
    double pitch;
    double roll;
};

struct DepthRange
{
    float zNear;
    float zFar;
};

struct ScreenResolution
{
    float width;
    float height;

    float getAspectRatio(){return width/height;};
};

struct CameraState
{
    CameraVectors orientationVectors; // Camera position and orientation vectors

    TiltAngles tiltAngles; // Camera tilt angles

    ScreenResolution resolution;

    DepthRange depthRange;

    glm::vec2 previousMousePosition; // 

    glm::vec2 mouseOffset; //

    float lookSensitivity; // Sensitivity camera has to mouse movement

    float movementSpeed; // Speed at which camera will move

    float fov;
};


class Camera
{
    public:
        Camera(float width, float height);

        void processMouseInput(double xPosition, double yPosition);
        void processScrollInput(double xPosition, double yPosition);
        void processKeyboardInput(GLFWwindow * glfwWindow);

        glm::mat4 calculateViewMatrix()
        {
            return glm::lookAt(cameraState.orientationVectors.cameraPosition, cameraState.orientationVectors.cameraPosition + cameraState.orientationVectors.cameraFront, cameraState.orientationVectors.cameraUp);
        }

        glm::mat4 calculateProjectionMatrix()
        {
            return glm::perspective(glm::radians(cameraState.fov), cameraState.resolution.getAspectRatio(), cameraState.depthRange.zNear,cameraState.depthRange.zFar);
        }

        void updateScreenResolution(float width, float height)
        {
            cameraState.resolution.width = width;
            cameraState.resolution.height = height;

        }

    private:
        CameraState cameraState;
     
        void initialiseCameraState(float width, float height); //Initilisation function TODO: these values should be input from the game logic


};

}


#endif

