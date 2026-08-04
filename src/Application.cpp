//
// Created by Citarlia on 2026/7/28.
//

#include "../include/Application.h"

Application* Application::instance = nullptr;
Application::Application() {

}

void Application::frameBufferResizeCallBack(GLFWwindow *window, int width, int height) {
    if (Application::getInstance()->resize_call_back_ != nullptr) {
        Application::getInstance()->resize_call_back_(width, height);
    }
}

Application::~Application() {

}

Application *Application::getInstance() {
    if (instance == nullptr) {
        instance = new Application;
    }
    return instance;
}

bool Application::init(const int& w, const int& h) {
    width = w;
    height = h;
    if (!glfwInit()) {
        std::cerr << "GLFW初始化失败！\n";
        return false;
    }

    window = glfwCreateWindow(width, height, "openGL test", nullptr, nullptr);
    if (!window) {
        std::cerr << "窗口加载失败！\n";
        return false;
    }

    glfwMakeContextCurrent(window); // 将窗口设为当前上下文
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        return false;
    }
    glfwSetFramebufferSizeCallback(window, frameBufferResizeCallBack);

    return true;
}

bool Application::update() {
    if (glfwWindowShouldClose(window)) {
        return false;
    }
    glfwSwapBuffers(window);
    glfwPollEvents();
    return true;
}

void Application::destroy() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Application::setCursorPosCallBack(CursorCallBack cursor_call_back) {
    glfwSetCursorPosCallback(window, cursor_call_back);
}

void Application::setMouseButtonCallBack(MouseButtonCallBack mouse_button_call_back) {
    glfwSetMouseButtonCallback(window, mouse_button_call_back);
}

void Application::setScrollCallback(ScrollCallBack scroll_call_back) {
    glfwSetScrollCallback(window, scroll_call_back);
}

void Application::setKeyCallBack(KeyCallBack key_call_back) {
    glfwSetKeyCallback(window, key_call_back);
}

void Application::setCursorMode(GLenum mode) {
    glfwSetInputMode(window, GLFW_CURSOR, mode);
}
