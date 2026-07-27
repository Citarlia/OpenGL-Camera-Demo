//
// Created by Citarlia on 2026/7/22.
//

#ifndef TEXTURE_TEXTURE_H
#define TEXTURE_TEXTURE_H
#include <iostream>
#include <string>
#include <glad//glad.h>
#include <GLFW/glfw3.h>

#include "stb_image.h"


class Texture {
    GLuint mTextureID {0};
    int width {0};
    int height {0};
    int format {0};
    unsigned int mUnit {0};
public:
    Texture(const std::string& path, unsigned int unit);
    ~Texture();
    void setFilter(GLenum pname, GLint param);
    void setWrapper(GLenum pname, GLint param);
    void setSampler(GLuint shader, const std::string& name);
    void bind();
    void unbind();
};


#endif //TEXTURE_TEXTURE_H
