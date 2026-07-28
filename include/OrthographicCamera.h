//
// Created by Citarlia on 2026/7/28.
//

#ifndef TEXTURE_ORTHOGRAPHICCAMERA_H
#define TEXTURE_ORTHOGRAPHICCAMERA_H
#include "Camera.h"


class OrthographicCamera : public Camera {
public:
    float left = 0;
    float right = 0;
    float bottom = 0;
    float top = 0;
    float near = 0;
    float far = 0;

    OrthographicCamera(float l, float r,  float b, float t, float n, float f);
    ~OrthographicCamera();
    mat4 getProjectionMatrix() override;
};


#endif //TEXTURE_ORTHOGRAPHICCAMERA_H
