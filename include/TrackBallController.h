//
// Created by Citarlia on 2026/7/28.
//

#ifndef TEXTURE_TRACKBALLCONTROLLER_H
#define TEXTURE_TRACKBALLCONTROLLER_H


#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
using namespace glm;

class Camera;   // 前向声明

class TrackBallController {
public:
    // 构造时传入目标摄像机、观察目标点、初始距离
    TrackBallController(Camera* camera, const vec3& target = vec3(0.0f), float distance = 5.0f);

    // 设置灵敏度（弧度/像素）
    void setSensitivity(float sensitivity) { m_sensitivity = sensitivity; }
    void setScrollSensitivity(float scrollSensitivity) { m_scrollSensitivity = scrollSensitivity; }

    // 启用/禁用控制器（例如防止冲突）
    void setEnabled(bool enabled) { m_enabled = enabled; }

    // 更新摄像机矩阵（应在渲染循环中调用，或者自动在回调中更新）
    void updateCamera();

    // ---- 静态回调函数，用于注册到 GLFW ----
    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void cursorPosCallback(GLFWwindow* window, double xpos, double ypos);
    static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
    static void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods);

private:
    Camera* m_camera;
    vec<3, float> m_target;
    float m_radius;   // 摄像机到目标的距离
    float m_yaw;      // 水平旋转角（弧度）
    float m_pitch;    // 垂直旋转角（弧度）

    float m_sensitivity;
    float m_scrollSensitivity;
    bool m_enabled;

    // 较上一帧的偏移量
    double dx;
    double dy;

    // 鼠标拖拽状态
    bool m_leftIsDragging;
    bool m_rightIsDragging;
    bool m_middleIsDragging;
    bool m_scrollMoved;
    double m_lastX, m_lastY;

    // 内部辅助：将球坐标转为位置
    vec3 sphericalToCartesian() const;
};


#endif //TEXTURE_TRACKBALLCONTROLLER_H
