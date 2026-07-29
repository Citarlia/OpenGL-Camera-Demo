//
// Created by Citarlia on 2026/7/28.
//

#include "CameraController.h"

CameraController::CameraController() {
    keyMap.emplace(GLFW_KEY_W, false);
    keyMap.emplace(GLFW_KEY_A, false);
    keyMap.emplace(GLFW_KEY_S, false);
    keyMap.emplace(GLFW_KEY_D, false);
    keyMap.emplace(GLFW_KEY_SPACE, false);
    keyMap.emplace(GLFW_KEY_LEFT_SHIFT, false);
    keyMap.emplace(GLFW_KEY_RIGHT_SHIFT, false);
}

CameraController::~CameraController() = default;
