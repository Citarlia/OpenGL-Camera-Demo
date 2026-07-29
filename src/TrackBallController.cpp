//
// Created by Citarlia on 2026/7/28.
//

#include "TrackBallController.h"
#include "Camera.h"
#include <glm/gtc/constants.hpp>
#include <algorithm>

TrackBallController::TrackBallController(Camera* camera, const vec3& target, float distance)
    : m_camera(camera)
    , m_target(target)
    , m_radius(distance)
    , m_yaw(0.0f)
    , m_pitch(0.0f)
    , m_sensitivity(0.005f)        // 默认灵敏度
    , m_scrollSensitivity(0.1f)    // 缩放步长
    , m_enabled(true)
    , m_isDragging(false)
    , m_lastX(0.0)
    , m_lastY(0.0)
{
    // 初始化位置（默认在 Z 轴正方向）
    updateCamera();
}

vec3 TrackBallController::sphericalToCartesian() const {
    vec3 pos;
    pos.x = m_radius * std::cos(m_pitch) * std::sin(m_yaw);
    pos.y = m_radius * std::sin(m_pitch);
    pos.z = m_radius * std::cos(m_pitch) * std::cos(m_yaw);
    return pos + m_target;
}

void TrackBallController::updateCamera() {
    if (!m_camera) return;
    m_camera->position = sphericalToCartesian();
    m_camera->viewPoint = m_target;
    // 注意：如果 Camera 的构造函数或 getViewMatrix 中依赖了 front/right/up 的计算，
    // 你可能需要显式更新它们（例如在 getViewMatrix 中重新计算），但通常 lookAt 会处理。
}

// ---------- 静态回调函数 ----------

void TrackBallController::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    auto* controller = static_cast<TrackBallController*>(glfwGetWindowUserPointer(window));
    if (!controller || !controller->m_enabled) return;

    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if (action == GLFW_PRESS) {
            controller->m_isDragging = true;
            glfwGetCursorPos(window, &controller->m_lastX, &controller->m_lastY);
        } else if (action == GLFW_RELEASE) {
            controller->m_isDragging = false;
        }
    }
}

void TrackBallController::cursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
    auto* controller = static_cast<TrackBallController*>(glfwGetWindowUserPointer(window));
    if (!controller || !controller->m_enabled || !controller->m_isDragging) return;

    double dx = xpos - controller->m_lastX;
    double dy = ypos - controller->m_lastY;
    controller->m_lastX = xpos;
    controller->m_lastY = ypos;

    // 应用灵敏度
    controller->m_yaw   -= static_cast<float>(dx) * controller->m_sensitivity;
    controller->m_pitch += static_cast<float>(dy) * controller->m_sensitivity;  // 屏幕 y 向上，所以反号

    // 限制 pitch 防止万向锁（-89° ~ 89°）
    const float maxPitch = radians(89.0f);
    controller->m_pitch = std::clamp(controller->m_pitch, -maxPitch, maxPitch);

    // 更新摄像机
    controller->updateCamera();
}

void TrackBallController::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    auto* controller = static_cast<TrackBallController*>(glfwGetWindowUserPointer(window));
    if (!controller || !controller->m_enabled) return;

    // yoffset > 0 表示向上滚动（放大/拉近）
    controller->m_radius -= static_cast<float>(yoffset) * controller->m_scrollSensitivity;
    // 防止距离太近或穿模
    controller->m_radius = std::max(controller->m_radius, 0.1f);

    controller->updateCamera();
}