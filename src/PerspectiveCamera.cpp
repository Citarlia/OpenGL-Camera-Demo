//
// Created by Citarlia on 2026/7/28.
//

#include "../include/PerspectiveCamera.h"

PerspectiveCamera::PerspectiveCamera(float f, float a, float n, float fa)
    : fov(f), aspect(a), near(n), far(fa) {
}

PerspectiveCamera::~PerspectiveCamera() = default;

mat4 PerspectiveCamera::getProjectionMatrix() {
    return perspective(radians(fov), aspect, near, far);
}
