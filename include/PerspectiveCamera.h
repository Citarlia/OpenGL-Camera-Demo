//
// Created by Citarlia on 2026/7/28.
//

#ifndef TEXTURE_PERSPECTIVECAMERA_H
#define TEXTURE_PERSPECTIVECAMERA_H
#include "Camera.h"


class PerspectiveCamera : public Camera {
public:
    float fov; // 这里以degree为单位储存，使用时使用redians转换
    float aspect; // 宽高比
    float near;
    float far;

    PerspectiveCamera(float f = 45.0f, float a = 800.0f/600.f, float n = 0.1f, float fa = 100.0f);
    ~PerspectiveCamera();
    mat4 getProjectionMatrix() override;

};


#endif //TEXTURE_PERSPECTIVECAMERA_H
