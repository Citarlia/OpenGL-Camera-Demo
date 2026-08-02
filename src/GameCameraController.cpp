//
// Created by Citarlia on 2026/7/30.
//

#include "../include/GameCameraController.h"

#include <algorithm>
#include <ranges>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

GameCameraController::GameCameraController(Camera *camera)
    : m_camera(camera)
    , m_currentX(0)
    , m_currentY(0)
    , m_speed(5.0f)
    , m_sensitivity(0.05f)
    , m_dx(0)
    , m_dy(0)
    , m_pitch(0.0)
    , m_yaw(0.0)
    , m_enabled(true)
    , m_initialized(true)
    , hasKeyPressed(false)
{
    m_keyMap.emplace(GLFW_KEY_W, false);
    m_keyMap.emplace(GLFW_KEY_A, false);
    m_keyMap.emplace(GLFW_KEY_S, false);
    m_keyMap.emplace(GLFW_KEY_D, false);
    m_keyMap.emplace(GLFW_KEY_R, false);
    m_keyMap.emplace(GLFW_KEY_SPACE, false);
    m_keyMap.emplace(GLFW_KEY_LEFT_SHIFT, false);
    m_keyMap.emplace(GLFW_KEY_RIGHT_SHIFT, false);

}

GameCameraController::~GameCameraController() = default;

// 回调函数：仅维护状态
void GameCameraController::keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods) {
    auto* controller = static_cast<GameCameraController*>(glfwGetWindowUserPointer(window));
    if (!controller || !controller->m_enabled) return;

    if (action == GLFW_PRESS) {
        controller->m_keyMap[key] = true;
    } else if (action == GLFW_RELEASE) {
        controller->m_keyMap[key] = false;  // 只清除这一个键
    }
    // 注意：这里不再调用 updateCamera()
}


void GameCameraController::cursorPosCallBack(GLFWwindow* window, double xpos, double ypos) {
    auto* controller = static_cast<GameCameraController*>(glfwGetWindowUserPointer(window));
    if (!controller || !controller->m_enabled) return;

    if (controller->m_initialized) {
        controller->m_currentX = xpos;
        controller->m_currentY = ypos;
        controller->m_initialized = false;
        return;
    }

    double dx = xpos - controller->m_currentX;
    double dy = ypos - controller->m_currentY;

    controller->m_currentX = xpos;
    controller->m_currentY = ypos;

    controller->m_yaw += static_cast<float>(controller->m_sensitivity * dx);
    controller->m_pitch -= static_cast<float>(controller->m_sensitivity * dy);

    const float max_pitch = 89.0f;
    controller->m_pitch = std::clamp(controller->m_pitch, -max_pitch, max_pitch);

    vec3 front;
    front.x = cos(radians(controller->m_pitch)) * sin(radians(controller->m_yaw));
    front.y = sin(radians(controller->m_pitch));
    front.z = -cos(radians(controller->m_pitch)) * cos(radians(controller->m_yaw));
    controller->m_camera->front = normalize(front);

    vec3 worldUp(0.0f, 1.0f, 0.0f);
    controller->m_camera->right = normalize(cross(worldUp, controller->m_camera->front));
    controller->m_camera->up = normalize(cross(controller->m_camera->front, controller->m_camera->right));

    controller->m_camera->viewPoint = controller->m_camera->position + controller->m_camera->front;

}

void GameCameraController::scrollCallBack(GLFWwindow *window, double xoffset, double yoffset) {

}

// 每帧调用的更新函数（在主循环中调用）
void GameCameraController::update(const float deltaTime) {
    if (!m_camera || !m_enabled) return;

    // 计算移动方向（归一化，防止斜向速度过快）
    vec3 moveDir(0.0f);
    if (m_keyMap[GLFW_KEY_W]) moveDir += m_camera->front;
    if (m_keyMap[GLFW_KEY_S]) moveDir -= m_camera->front;
    if (m_keyMap[GLFW_KEY_A]) moveDir += m_camera->right;
    if (m_keyMap[GLFW_KEY_D]) moveDir -= m_camera->right;
    if (m_keyMap[GLFW_KEY_SPACE]) moveDir += m_camera->up;
    if (m_keyMap[GLFW_KEY_LEFT_SHIFT] || m_keyMap[GLFW_KEY_RIGHT_SHIFT]) 
        moveDir -= m_camera->up;

    // 如果没有任何按键，直接返回
    if (length(moveDir) < 0.001f) return;

    // 归一化并乘以速度和时间
    moveDir = normalize(moveDir);
    float speed = m_speed * deltaTime;  // 使用 deltaTime
    m_camera->position += moveDir * speed;
    m_camera->viewPoint += moveDir * speed;  // 注意：这里 viewPoint 和 position 同步移动是否合理？取决于你的相机设计
}

vec3 GameCameraController::sphericalToCartesian() {
    vec3 pos;
    pos.x = cos(radians(m_pitch)) * sin(radians(m_yaw));
    pos.y = sin(radians(m_pitch));
    pos.z = cos(radians(m_pitch)) * cos(radians(m_yaw));
    return pos;
}
