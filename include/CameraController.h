//
// Created by Citarlia on 2026/7/28.
//

#ifndef TEXTURE_CAMERACONTROLLER_H
#define TEXTURE_CAMERACONTROLLER_H

#include <iostream>
#include <map>
#include <GLFW/glfw3.h>

#include "Camera.h"


class CameraController {
public:
    bool mouseLeftKeyDown = false;
    bool mouseRightKeyDown = false;
    bool mouseMiddleKeyDown = false;
    double currentX = 0, currentY = 0;
    std::map<int, bool> keyMap{}; // 检查各个按键是否按下
    double sensitive = 0.1f;
    Camera* camera {nullptr};

    CameraController();
    ~CameraController();

    virtual void update(GLFWwindow* window);

    virtual void onMouse(GLFWwindow* window, int button, int action, int mods);
    virtual void onCursor();
    virtual void onKey();
};


#endif //TEXTURE_CAMERACONTROLLER_H
