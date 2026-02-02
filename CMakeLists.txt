cmake_minimum_required(VERSION 3.26)
project(snake)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(glfw)

include_directories(glad/include)
set(GLAD_LIB "${CMAKE_CURRENT_SOURCE_DIR}/glad/src/glad.c")

add_executable(snake main.cpp ${GLAD_LIB})
target_link_libraries(snake glfw)
