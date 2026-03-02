#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
private:
    GLFWwindow *window;

    Window();
public:
    Window(Window &other) = delete;
    void operator=(const Window &) = delete;

    static GLFWwindow* getInstance();
};