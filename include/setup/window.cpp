#include "window.hpp"

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
    int SCREEN_WIDTH = GetSystemMetrics(SM_CXSCREEN) * 4;
    int SCREEN_HEIGHT = GetSystemMetrics(SM_CYSCREEN) * 4;
#else
    int SCREEN_WIDTH = 1600;
    int SCREEN_HEIGHT = 1200;
#endif

Window::Window() {
    this->window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake 3D", nullptr, nullptr);
}

GLFWwindow* Window::getInstance() {
    static auto *instance = new Window();
    return instance->window;
}