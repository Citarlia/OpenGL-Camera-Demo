//
// Created by Citarlia on 2026/7/30.
//

#ifndef OPENGLBASIC_GAMECAMERACONTROLLER_H
#define OPENGLBASIC_GAMECAMERACONTROLLER_H

#include <iostream>
#include <map>
#include "glm/glm.hpp"
#include "Camera.h"
#include "GLFW/glfw3.h"

using namespace glm;

class GameCameraController {
public:
    GameCameraController(Camera* camera);
    ~GameCameraController();

    // 设置灵敏度（弧度/像素）
    void setSensitivity(float sensitivity) { m_sensitivity = sensitivity; }
    void setScrollSensitivity(float scrollSensitivity) { m_sensitivity = scrollSensitivity; }

    // 启用/禁用控制器（例如防止冲突）
    void setEnabled(bool enabled) { m_enabled = enabled; }

    // 静态回调函数
    static void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void cursorPosCallBack(GLFWwindow*, double xpos, double ypos);
    static void scrollCallBack(GLFWwindow* window, double xoffset, double yoffset);

    // 更新摄像机
    void update(float deltaTime);
private:
    Camera* m_camera;

    // 当前鼠标位置
    double m_currentX;
    double m_currentY;

    float m_speed; // 移动速度
    float m_sensitivity; // 鼠标灵敏度

    float m_pitch; // 俯仰角
    float m_yaw; // 偏航角

    bool m_enabled; // 是否禁用控制器
    bool m_initialized;

    // 按键状态
    std::map<int, bool> m_keyMap; // 存储按下的键位
    bool hasKeyPressed;

    vec3 sphericalToCartesian() const;
};


#endif //OPENGLBASIC_GAMECAMERACONTROLLER_H
