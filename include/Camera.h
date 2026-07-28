//
// Created by Citarlia on 2026/7/28.
//

#ifndef TEXTURE_CAMERA_H
#define TEXTURE_CAMERA_H

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

class Camera {
public:
    vec3 position {0.0, 0.0, 1.0};
    vec3 viewPoint {0.0, 0.0, 0.0};
    vec3 right {1.0, 0.0, 0.0};
    vec3 front {0.0, 0.0, -1.0};
    vec3 up {0.0, 1.0, 0.0};

    Camera();

    ~Camera();
    mat4 getViewMatrix();
    virtual mat4 getProjectionMatrix() = 0;
};


#endif //TEXTURE_CAMERA_H
