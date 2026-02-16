#include <iostream>
#include <fstream>
#include <sstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <camera/camera.hpp>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
    int SCREEN_WIDTH = GetSystemMetrics(SM_CXSCREEN);
    int SCREEN_HEIGHT = GetSystemMetrics(SM_CYSCREEN);
#else
    int SCREEN_WIDTH = 1600;
    int SCREEN_HEIGHT = 1200;
#endif

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "3D Snake", nullptr, nullptr);
    if(!window) {
        std::cout << "Failed to initialize GLFWwindow." << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD." << std::endl;
        return -1;
    }

    std::ifstream vs;
    vs.open("../shaders/sampleVS.glsl", std::ios_base::in);
    if(!vs.is_open()) {
        std::cout << "Failed to open vertex shader." << std::endl;
        return -1;
    }

    std::stringstream vsText;
    vsText << vs.rdbuf();
    vs.close();

    std::string vsString = vsText.str();
    const char* vsCString = vsString.c_str();

    unsigned vsh;
    vsh = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vsh, 1, &vsCString, nullptr);
    glCompileShader(vsh);

    int success;
    char message[512];
    glGetShaderiv(vsh, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(vsh, 512, nullptr, message);
        std::cout << "Vertex shader compilation failed:\n" << message << std::endl;
        return -1;
    }

    std::ifstream fs;
    fs.open("../shaders/sampleFS.glsl", std::ios_base::in);
    if(!fs.is_open()) {
        std::cout << "Failed to open fragment shader." << std::endl;
        return -1;
    }

    std::stringstream fsText;
    fsText << fs.rdbuf();
    fs.close();

    std::string fsString = fsText.str();
    const char* fsCString = fsString.c_str();

    unsigned fsh;
    fsh = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fsh, 1, &fsCString, nullptr);
    glCompileShader(fsh);

    glGetShaderiv(fsh, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(fsh, 512, nullptr, message);
        std::cout << "Fragment shader compilation failed:\n" << message << std::endl;
        return -1;
    }

    unsigned shader;
    shader = glCreateProgram();
    glAttachShader(shader, vsh);
    glAttachShader(shader, fsh);
    glLinkProgram(shader);

    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shader, 512, nullptr, message);
        std::cout << "Shaders failed to link: " << message << std::endl;
        return -1;
    }
    glDeleteShader(vsh);
    glDeleteShader(fsh);

    float vertices[] = {
            -0.5f, -0.5f,  0.0f,    1.0f, 0.0f, 0.0f,
             0.5f, -0.5f,  0.0f,    0.0f, 1.0f, 0.0f,
             0.0f,  0.5f,  0.0f,    0.0f, 0.0f, 1.0f
    };

    unsigned VBO, VAO;

    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    while(!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}
