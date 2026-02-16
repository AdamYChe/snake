#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

constexpr float SENSITIVITY = 0.03f;
constexpr float ZOOM = 45.0f;
constexpr float SPEED = 2.5f;
constexpr float YAW = -90.0f;
constexpr float PITCH = 0.0f;

enum CameraMovement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    DOWN,
    UP
};

class Camera {
private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    float yaw;
    float pitch;

    float movementSpeed;
    float mouseSensitivity;
    float zoom;

    void updateCameraVectors();

public:
    explicit Camera(const glm::vec3 &position = glm::vec3(0.0f, 0.0f, -1.0f),
                    const glm::vec3 &up = glm::vec3(0.0f, 1.0f, 0.0f),
                    const float &yaw = YAW,
                    const float &pitch = PITCH);
    explicit Camera(const float &posX, const float &posY, const float &posZ,
                    const float &upX, const float &upY, const float &upZ,
                    const float &yaw, const float& pitch);

    [[nodiscard]] glm::mat4 getViewMatrix() const;
    void processKeyboard(CameraMovement direction, float deltaTime);
    void processMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch = true);
    void processMouseScroll(float yOffset);
};
