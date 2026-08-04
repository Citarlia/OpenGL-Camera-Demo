#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include "Application.h"
#include "FPSCounter.h"
#include "Shader.h"
#include "Texture.h"
#include "PerspectiveCamera.h"
#include "TrackBallController.h"
#include "GameCameraController.h"
using namespace glm;

void onResize(int width, int height) {
    glViewport(0, 0, width, height);
}

static void setTrackBallControllerCallBackRegistry(Application* application) {
    // 注册回调
    application->setCursorPosCallBack(TrackBallController::cursorPosCallBack);
    application->setMouseButtonCallBack(TrackBallController::mouseButtonCallBack);
    application->setScrollCallback(TrackBallController::scrollCallBack);
    application->setKeyCallBack(TrackBallController::keyCallBack);
}

static void setGameControllerCallBackRegistry(Application* application) {
    // 注册回调
    application->setCursorPosCallBack(GameCameraController::cursorPosCallBack);
    application->setScrollCallback(GameCameraController::scrollCallBack);
    application->setKeyCallBack(GameCameraController::keyCallBack);
    application->setCursorMode(GLFW_CURSOR_DISABLED);
}

float vertexes[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
       -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
       -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

       -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
       -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
       -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

       -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
       -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
       -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
       -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
       -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
       -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

       -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
       -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
       -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

       -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
       -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
       -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

int main() {

    Application* application = Application::getInstance();
    application->init();
    application->setResizeCallBack(onResize);

    GLFWwindow* window = application->getWindow();

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexes), vertexes, GL_STATIC_DRAW);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3*sizeof(float)));
    glBindVertexArray(0);

    // 设置着色器
    Shader shader = Shader({"../resource/MyShader.vert"}, {"../resource/MyShader.frag"});
    shader.createShader();

    // 设置纹理
    Texture texture = Texture({"../textures/sheri.png"}, 0);
    texture.setFilter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    texture.setWrapper(GL_TEXTURE_WRAP_S, GL_REPEAT);
    texture.setWrapper(GL_TEXTURE_WRAP_T, GL_REPEAT);
    texture.setSampler(shader.getProgramID(), {"sampler_"});

    // 设置摄像机
    PerspectiveCamera perspective_camera(45.0f, 800.0f/600.0f, 0.1f, 100.0f);

    // 设置控制器
    TrackBallController controller(&perspective_camera, glm::vec3(0.0f), 3.0f); // 距离设为3
    // 调整灵敏度
    controller.setSensitivity(0.005f);
    controller.setScrollSensitivity(0.2f);

    GameCameraController game_camera_controller(&perspective_camera);

    glClearColor(0.2, 0.3, 0.3, 1);
    // 开启深度检测
    glEnable(GL_DEPTH_TEST);
    // 将控制器指针存入窗口，供静态回调使用
    glfwSetWindowUserPointer(window, &game_camera_controller);
    setGameControllerCallBackRegistry(application);
    FPSCounter fpsCounter(2.0f);
    double lastTime = glfwGetTime();

    while (application->update()) {
        fpsCounter.tick();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shader.bind();
        glBindVertexArray(vao);

        double currentTime = glfwGetTime();
        auto deltaTime = static_cast<float>(currentTime - lastTime);
        lastTime = currentTime;

        // ... 处理输入、更新等
        game_camera_controller.update(deltaTime);
        // 模型矩阵
        mat4 model = translate(mat4(1.0), vec3(0.0, 0.0, 0.0));
        // 视图矩阵
        mat4 view =  perspective_camera.getViewMatrix();
        // 投影矩阵
        mat4 projection = perspective_camera.getProjectionMatrix();
        // 传入矩阵
        shader.setMatrix({"model"}, model);
        shader.setMatrix({"view"}, view);
        shader.setMatrix({"projection"}, projection);

        glDrawArrays(GL_TRIANGLES, 0 ,36);
    }

    application->destroy();

    return 0;
}