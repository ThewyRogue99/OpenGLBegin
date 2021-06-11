#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum class CameraDirection {
    NONE = 0,
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class Camera {
public:

    // position
    glm::vec3 cameraPos;

    // camera directional values
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;
    glm::vec3 cameraRight;

    glm::vec3 worldUp;

    // camera rotational values
    glm::vec3 cameraRotation; // x = pitch, y = yaw, z = roll

    float* pitch = &cameraRotation.x;
    float* yaw = &cameraRotation.y;
    float* roll = &cameraRotation.z;

    // camera movement values
    float speed;
    float sensitivity;
    float zoom;

    // default and initialize with position
    Camera(glm::vec3 position = glm::vec3(0.0f), bool isDefault = true);

    // change camera direction (mouse movement)
    void updateCameraDirection(double dx, double dy);

    // change camera position in certain direction (keyboard)
    void updateCameraPos(CameraDirection direction);

    // change camera zoom (scroll wheel)
    void updateCameraZoom(double dy);

    // get view matrix for camera
    glm::mat4 getViewMatrix();

    // get zoom value for camera
    float getZoom();

    static Camera* defaultCamera;

private:

    // change camera directional vectors based on movement
    void updateCameraVectors();
};