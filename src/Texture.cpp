//
// Created by Citarlia on 2026/7/22.
//

#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
Texture::Texture(const std::string &path, unsigned int unit):mUnit(unit) {
    // 读取图片
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &format, STBI_rgb_alpha);
    // 生成纹理并激活对象绑定
    glGenTextures(1, &mTextureID);
    // 激活纹理单元

    glActiveTexture(GL_TEXTURE0 + mUnit);
    // 绑定纹理对象
    glBindTexture(GL_TEXTURE_2D, mTextureID);
    // 传递纹理数据
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);    // 释放
    stbi_image_free(data);
}

Texture::~Texture() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::setFilter(GLenum pname, GLint param) {
    // 设置过滤器
    glTexParameteri(GL_TEXTURE_2D, pname, param);
    glTexParameteri(GL_TEXTURE_2D, pname, param);
}

void Texture::setWrapper(GLenum pname, GLint param) {
    // 纹理包装
    glTexParameteri(GL_TEXTURE_2D, pname, param);
    glTexParameteri(GL_TEXTURE_2D, pname, param);
}

void Texture::setSampler(GLuint shader, const std::string &name) {
    GLint sampler_location = glGetUniformLocation(shader, name.c_str());
    glUniform1i(sampler_location, mUnit);
}

void Texture::bind() {
    glBindTexture(GL_TEXTURE_2D, mTextureID);
}

void Texture::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}
