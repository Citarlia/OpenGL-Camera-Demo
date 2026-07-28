//
// Created by Citarlia on 2026/7/28.
//

#include "../include/OrthographicCamera.h"

OrthographicCamera::OrthographicCamera(float l, float r, float b, float t, float n, float f)
    : left(l), right(r), bottom(b), top(t), near(n), far(f) {
}

OrthographicCamera::~OrthographicCamera() = default;

mat4 OrthographicCamera::getProjectionMatrix() {
    return ortho(left, right, bottom, top, near, far);
}
