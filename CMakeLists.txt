cmake_minimum_required(VERSION 3.26)
project(snake)

set(CMAKE_CXX_STANDARD 23)

include_directories(lib) # glm

add_subdirectory(lib/glfw) # glfw

include_directories(lib/glad/include)   # glad
set(GLAD_LIB "${CMAKE_CURRENT_SOURCE_DIR}/lib/glad/src/glad.c")

add_executable(snake src/main.cpp ${GLAD_LIB}
        include/camera/camera.cpp
)
target_link_libraries(snake glfw)
target_include_directories(snake PUBLIC include)
