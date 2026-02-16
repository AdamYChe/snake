#include "camera.hpp"

void Camera::updateCameraVectors() {
    this->front = glm::normalize(glm::vec3(
        cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch)),
        sin(glm::radians(this->pitch)),
        sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch))
    ));

    this->right = glm::normalize(glm::cross(this->front, this->worldUp));
    this->up = glm::normalize(glm::cross(this->right, this->right));
}

Camera::Camera(const glm::vec3 &position, const glm::vec3 &up, const float &yaw, const float &pitch)
                : front(glm::vec3(0.0f, 0.0f, -1.0f)),
                movementSpeed(SPEED),
                mouseSensitivity(SENSITIVITY),
                zoom(ZOOM)
{
    this->position = position;
    this->worldUp = up;
    this->yaw = yaw;
    this->pitch = pitch;
    updateCameraVectors();
}

Camera::Camera(const float &posX, const float &posY, const float &posZ,
               const float &upX, const float &upY, const float &upZ,
               const float &yaw, const float& pitch)
                : front(glm::vec3(0.0f, 0.0f, -1.0f)),
                movementSpeed(SPEED),
                mouseSensitivity(SENSITIVITY),
                zoom(ZOOM)
{
    this->position = glm::vec3(posX, posY, posZ);
    this->worldUp = glm::vec3(upX, upY, upZ);
    this->yaw = yaw;
    this->pitch = pitch;
    updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(position, position + front, up);
}

void Camera::processKeyboard(CameraMovement direction, float deltaTime) {
    float velocity = movementSpeed * deltaTime;

    switch(direction) {
        case FORWARD:
            position += front * velocity;
            break;
        case BACKWARD:
            position -= front * velocity;
            break;
        case LEFT:
            position -= right * velocity;
            break;
        case RIGHT:
            position += right * velocity;
            break;
        case UP:
            position += up * velocity;
            break;
        case DOWN:
            position -= up * velocity;
            break;
    }
}

void Camera::processMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch) {
    xOffset *= mouseSensitivity;
    yOffset += mouseSensitivity;

    this->yaw += xOffset;
    this->pitch += yOffset;

    if(constrainPitch) {
        this->pitch = fminf(fmaxf(this->pitch, 0.01f), 89.9f);
    }

    updateCameraVectors();
}

void Camera::processMouseScroll(float yOffset) {
    this->zoom -= yOffset;
    this->zoom =fminf(fmaxf(this->zoom, 1.0f), 45.0f);
}