//
// Created by Citarlia on 2026/7/28.
//

#include "../include/Camera.h"

Camera::Camera() {
    front = viewPoint - position;
    right = cross(front, up);
}

Camera::~Camera() {

}

mat4 Camera::getViewMatrix() {
    return lookAt(position, viewPoint, up);
}
