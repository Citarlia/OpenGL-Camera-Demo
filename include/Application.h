//
// Created by Citarlia on 2026/7/28.
//

#ifndef TEXTURE_APPLICATION_H
#define TEXTURE_APPLICATION_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using ResizeCallBack = void(*)(int width, int height);

class Application {
    static Application* instance;
    Application();

    unsigned int width {0};
    unsigned int height {0};
    GLFWwindow* window {nullptr};
    ResizeCallBack resize_call_back_ {nullptr};

    // 定义触发了事件时进行的操作，类内函数，因此使用static进行修饰表示为类而不是实例所有
    static void frameBufferResizeCallBack(GLFWwindow* window, int width, int height);

public:
    ~Application();
    static Application* getInstance();

    bool init(const int& w = 800, const int& h = 600);
    bool update();
    void destroy();

    // 设置触发窗口调整大小时运行的方法 这是对外接口，从外界向类中传递函数指针
    void setResizeCallBack(ResizeCallBack resize_call_back) {resize_call_back_ = resize_call_back;}

    unsigned int getWidth() const {return width;}
    unsigned int getHeight() const {return height;}
    GLFWwindow* getWindow() const {return window;}
};


#endif //TEXTURE_APPLICATION_H
