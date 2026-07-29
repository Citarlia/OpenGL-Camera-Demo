//
// Created by Citarlia on 2026/7/28.
//

#include "../include/Camera.h"

Camera::Camera() = default;

Camera::~Camera() = default;

mat4 Camera::getViewMatrix() {
    front = viewPoint - position;
    right = cross(front, up);
    return lookAt(position, viewPoint, up);
}
