//
// Created by Citarlia on 2026/7/28.
//

#include "TrackBallController.h"
#include "Camera.h"
#include <glm/gtc/constants.hpp>
#include <algorithm>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

TrackBallController::TrackBallController(Camera* camera, const vec3& target, float distance)
    : m_camera(camera)
    , m_target(target)
    , m_radius(distance)
    , m_yaw(0.0f)
    , m_pitch(0.0f)
    , m_sensitivity(0.005f)        // 默认灵敏度
    , m_scrollSensitivity(0.1f)    // 缩放步长
    , m_enabled(true)
    , dx(0.0f)
    , dy(0.0f)
    , m_leftIsDragging(false)
    , m_middleIsDragging(false)
    , m_rightIsDragging(false)
    , m_scrollMoved(false)
    , m_lastX(0.0)
    , m_lastY(0.0)
{
    // 初始化位置（默认在 Z 轴正方向）
    m_camera->position = vec3(0.0, 0.0, m_radius);
    m_camera->viewPoint = vec3(0.0);
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

    if (m_scrollMoved) {
        m_camera->position = sphericalToCartesian();
        m_camera->viewPoint = m_target;
    }

    if (m_leftIsDragging) {
        m_camera->position = sphericalToCartesian();
        m_camera->viewPoint = m_target;
    }

    if (m_middleIsDragging) {
        // 将摄像机位置和摄像机观察点同时向鼠标平移方向移动
        m_camera->position -= m_scrollSensitivity * 0.005f * static_cast<float>(dx) * m_camera->right;
        m_camera->position += m_scrollSensitivity * 0.01f * static_cast<float>(dy) * m_camera->up;
        m_target -= m_scrollSensitivity * 0.005f * static_cast<float>(dx) * m_camera->right;
        m_target += m_scrollSensitivity * 0.01f * static_cast<float>(dy) * m_camera->up;
        m_camera->viewPoint = m_target;
    }
    // 注意：如果 Camera 的构造函数或 getViewMatrix 中依赖了 front/right/up 的计算，
    // 可能需要显式更新它们（例如在 getViewMatrix 中重新计算），但通常 lookAt 会处理。
}

// ---------- 静态回调函数 ----------

void TrackBallController::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    auto* controller = static_cast<TrackBallController*>(glfwGetWindowUserPointer(window));
    if (!controller || !controller->m_enabled) return;

    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if (action == GLFW_PRESS) {
            controller->m_leftIsDragging = true;
            glfwGetCursorPos(window, &controller->m_lastX, &controller->m_lastY);
        } else if (action == GLFW_RELEASE) {
            controller->m_leftIsDragging = false;
        }
    }

    if (button == GLFW_MOUSE_BUTTON_MIDDLE) {
        if (action == GLFW_PRESS) {
            controller->m_middleIsDragging = true;
            glfwGetCursorPos(window, &controller->m_lastX, &controller->m_lastY);
        } else if (action == GLFW_RELEASE) {
            controller->m_middleIsDragging = false;
        }
    }

    if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        if (action == GLFW_PRESS) {
            controller->m_rightIsDragging = true;
            glfwGetCursorPos(window, &controller->m_lastX, &controller->m_lastY);
        } else if (action == GLFW_RELEASE) {
            controller->m_rightIsDragging = false;
        }
    }
}

void TrackBallController::cursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
    auto* controller = static_cast<TrackBallController*>(glfwGetWindowUserPointer(window));
    if (!controller || !controller->m_enabled || (!controller->m_leftIsDragging && !controller->m_rightIsDragging && !controller->m_middleIsDragging)) return;
    if (controller->m_leftIsDragging) {
        controller->dx = xpos - controller->m_lastX;
        controller->dy = ypos - controller->m_lastY;
        controller->m_lastX = xpos;
        controller->m_lastY = ypos;

        // 应用灵敏度
        controller->m_yaw   -= static_cast<float>(controller->dx) * controller->m_sensitivity;
        controller->m_pitch += static_cast<float>(controller->dy) * controller->m_sensitivity;  // 屏幕 y 向上，所以反号

        // 限制 pitch 防止万向锁（-89° ~ 89°）
        const float maxPitch = radians(89.0f);
        controller->m_pitch = std::clamp(controller->m_pitch, -maxPitch, maxPitch);

        // 更新摄像机
        controller->updateCamera();
    }
    if (controller->m_middleIsDragging) {
        controller->dx = xpos - controller->m_lastX;
        controller->dy = ypos - controller->m_lastY;
        controller->m_lastX = xpos;
        controller->m_lastY = ypos;

        controller->updateCamera();
    }
}

void TrackBallController::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    auto* controller = static_cast<TrackBallController*>(glfwGetWindowUserPointer(window));
    if (!controller || !controller->m_enabled) return;
    // 监视滚轮是否转动
    controller->m_scrollMoved = true;
    // yoffset > 0 表示向上滚动（放大/拉近）
    controller->m_radius -= static_cast<float>(yoffset) * controller->m_scrollSensitivity;
    // 防止距离太近或穿模
    controller->m_radius = std::max(controller->m_radius, 0.1f);

    controller->updateCamera();

    controller->m_scrollMoved = false;
}

void TrackBallController::keyCallBack(GLFWwindow *window, int key, int scancode, int action, int mods) {
    auto* controller = static_cast<TrackBallController*>(glfwGetWindowUserPointer(window));
    if (!controller || !controller->m_enabled) return;

    // 按下R键复原
    if (key == GLFW_KEY_R && action == GLFW_PRESS) {
        controller->m_pitch = 0.0f;
        controller->m_yaw = 0.0f;
        controller->m_target = vec3(0.0);
        controller->m_camera->position = vec3(0.0, 0.0, controller->m_radius);
        controller->m_camera->viewPoint = vec3(0.0, 0.0, 0.0);
    }
}
