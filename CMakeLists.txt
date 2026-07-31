cmake_minimum_required(VERSION 3.28)
project(OpenGLBasic)

set(CMAKE_CXX_STANDARD 20)

# 1. 设置头文件搜索路径
include_directories(include)
set(RESOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/resource)
set(TEXTURES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/textures)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resource
        DESTINATION ${CMAKE_BINARY_DIR})
# 2. 设置库文件搜索路径
link_directories(lib)

# 3. 添加源文件 (记得把 glad.c 加进来)
add_executable(OpenGLBasic src/glad.c main.cpp src/Shader.cpp
        include/stb_image.h
        src/Texture.cpp
        src/Application.cpp
        src/Camera.cpp
        src/OrthographicCamera.cpp
        src/PerspectiveCamera.cpp
        src/TrackBallController.cpp
        src/GameCameraController.cpp
        include/FPSCounter.h
)

# 4. 链接库
target_include_directories(OpenGLBasic PRIVATE include)
target_link_libraries(OpenGLBasic glfw3 opengl32)
