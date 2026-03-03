#include "Camera.h"


namespace gfx {

//TODO: Possibly need to change types used in structures. Static casting a lot of doubles to floats at the moment, maybe should just use floats?

// 3D camera module, 
Camera::Camera(float width, float height)
{
    initialiseCameraState(width, height);
};

void Camera::initialiseCameraState(float width, float height)
{
    cameraState.orientationVectors.cameraPosition = initialCameraPosition;
    cameraState.orientationVectors.cameraFront    = initialCameraFront;
    cameraState.orientationVectors.cameraUp       = initialCameraUp;

    cameraState.tiltAngles.yaw   = initialYaw;
    cameraState.tiltAngles.pitch = initialPitch;
    cameraState.tiltAngles.roll  = initialRoll;

    cameraState.previousMousePosition.x = initialPreviousX;
    cameraState.previousMousePosition.y = initialPreviousY;

    cameraState.mouseOffset.x = initialOffsetX;
    cameraState.mouseOffset.y = initialOffsetY;

    cameraState.lookSensitivity = initialLookSensitivity;
    
    cameraState.movementSpeed = initialCameraMoveSpeed;

    cameraState.fov = initialFOV;

    cameraState.resolution.width  = width;
    cameraState.resolution.height = height;

    cameraState.depthRange.zNear = initialZNear;
    cameraState.depthRange.zFar  = initialZFar;
}

void Camera::processMouseInput(double xPosition, double yPosition)
{
    static bool firstMouse = true; // Check used to smooth cursor selecting/entering window for first time

    if (firstMouse)
    {
        cameraState.previousMousePosition.x = static_cast<float>(xPosition);
        cameraState.previousMousePosition.y = static_cast<float>(yPosition);
        firstMouse = false;
    }

    cameraState.mouseOffset.x = static_cast<float>(xPosition) - cameraState.previousMousePosition.x;
    cameraState.mouseOffset.y = cameraState.previousMousePosition.y - static_cast<float>(yPosition);

    cameraState.previousMousePosition.x = static_cast<float>(xPosition);
    cameraState.previousMousePosition.y = static_cast<float>(yPosition);

    cameraState.mouseOffset.x *= cameraState.lookSensitivity;
    cameraState.mouseOffset.y *= cameraState.lookSensitivity;

    cameraState.tiltAngles.yaw += cameraState.mouseOffset.x;
    cameraState.tiltAngles.pitch += cameraState.mouseOffset.y;


	if (cameraState.tiltAngles.pitch > highPitchLimit)
		cameraState.tiltAngles.pitch = highPitchLimit;
	if (cameraState.tiltAngles.pitch < lowPitchLimit)
		cameraState.tiltAngles.pitch = lowPitchLimit;

	glm::vec3 direction;
	direction.x = static_cast<float>(cos(glm::radians(cameraState.tiltAngles.yaw)) * cos(glm::radians(cameraState.tiltAngles.pitch)));
	direction.y = static_cast<float>(sin(glm::radians(cameraState.tiltAngles.pitch)));
	direction.z = static_cast<float>(sin(glm::radians(cameraState.tiltAngles.yaw)) * cos(glm::radians(cameraState.tiltAngles.pitch)));
	cameraState.orientationVectors.cameraFront = glm::normalize(direction);
}


void Camera::processScrollInput(double xOffset, double yOffset)
{
	cameraState.fov -= (float)yOffset;
	if (cameraState.fov < lowFovLimit)
		cameraState.fov = lowFovLimit;
	if (cameraState.fov > highFovLimit)
		cameraState.fov = highFovLimit;
}

void Camera::processKeyboardInput()
{
	// if (glfwGetKey(glfwWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	// 	glfwSetWindowShouldClose(glfwWindow, true);
	// if (glfwGetKey(glfwWindow, GLFW_KEY_W) == GLFW_PRESS)
    //     cameraState.orientationVectors.cameraPosition += cameraState.movementSpeed * cameraState.orientationVectors.cameraFront;
	// if (glfwGetKey(glfwWindow, GLFW_KEY_S) == GLFW_PRESS)
    //     cameraState.orientationVectors.cameraPosition -= cameraState.movementSpeed * cameraState.orientationVectors.cameraFront;
	// if (glfwGetKey(glfwWindow, GLFW_KEY_A) == GLFW_PRESS)
    //     cameraState.orientationVectors.cameraPosition -= glm::normalize(cross(cameraState.orientationVectors.cameraFront, cameraState.orientationVectors.cameraUp)) * cameraState.movementSpeed;
	// if (glfwGetKey(glfwWindow, GLFW_KEY_D) == GLFW_PRESS)
    //     cameraState.orientationVectors.cameraPosition += glm::normalize(cross(cameraState.orientationVectors.cameraFront, cameraState.orientationVectors.cameraUp)) * cameraState.movementSpeed;

}


















}