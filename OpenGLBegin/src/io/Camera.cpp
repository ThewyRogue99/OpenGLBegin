#include "camera.h"
#include "../engine/Engine.h"

Camera* Camera::defaultCamera = nullptr;

// default and initialize with position
Camera::Camera(glm::vec3 position, bool isDefault)
    : cameraPos(position),
    worldUp(glm::vec3(0.f, 1.f, 0.f)),
    cameraRotation(0.f, 270.f, 0.f),
    speed(2.5f),
    sensitivity(1.5f),
    zoom(45.f),
    cameraFront(glm::vec3(1.f, 0.f, 0.f)) {

    if (isDefault)
        defaultCamera = this;

    updateCameraVectors(); 
}

// change camera direction (mouse movement)
void Camera::updateCameraDirection(double dx, double dy)
{
    float deltaTime = Engine::GetDeltaTime();

    float copyPitch = *pitch + (((float)dy * deltaTime) * sensitivity * 20.f);
    float copyYaw = *yaw + (((float)dx * deltaTime) * sensitivity * 20.f);

    if (copyPitch > 89.f)
        *pitch = 89.f;
    else if (copyPitch < -89.f)
        *pitch = -89.f;
    else
        *pitch = copyPitch;

    if (copyYaw > 360.f)
        *yaw = 0.f;
    else if (copyYaw < 0.f)
        *yaw = 360.f;
    else
        *yaw = copyYaw;

    updateCameraVectors();
}

// change camera position in certain direction (keyboard)
void Camera::updateCameraPos(CameraDirection direction)
{
    float deltaTime = Engine::GetDeltaTime();

    float velocity = (float)deltaTime * speed;

    switch (direction)
    {
    case CameraDirection::FORWARD:
        cameraPos += cameraFront * velocity;
        break;
    case CameraDirection::BACKWARD:
        cameraPos -= cameraFront * velocity;
        break;
    case CameraDirection::RIGHT:
        cameraPos += cameraRight * velocity;
        break;
    case CameraDirection::LEFT:
        cameraPos -= cameraRight * velocity;
        break;
    case CameraDirection::UP:
        cameraPos += cameraUp * velocity;
        break;
    case CameraDirection::DOWN:
        cameraPos -= cameraUp * velocity;
        break;
    }
}

// change camera zoom (scroll wheel)
void Camera::updateCameraZoom(double dy)
{
    if (zoom >= 1.0f && zoom <= 45.0f) 
        zoom -= (float)dy;
    else if (zoom < 1.0f)
        zoom = 1.0f;
    else
        zoom = 45.0f;
}

// get view matrix for camera
glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

// get zoom value for camera
float Camera::getZoom()
{
    return zoom;
}

// change camera directional vectors based on movement
void Camera::updateCameraVectors() {
    glm::vec3 direction;
    direction.x = cos(glm::radians(*yaw)) * cos(glm::radians(*pitch));
    direction.y = sin(glm::radians(*pitch));
    direction.z = sin(glm::radians(*yaw)) * cos(glm::radians(*pitch));
    cameraFront = glm::normalize(direction);

    cameraRight = glm::normalize(glm::cross(cameraFront, worldUp));
    cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront));
}