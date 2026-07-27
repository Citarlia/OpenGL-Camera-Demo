#ifndef EBO_SHADER_H
#define EBO_SHADER_H

#include <iostream>
#include <fstream>
#include <glad/glad.h>
#include <string>
#include <map>
#include <assert.h>


class Shader
{
private:
    /* data */
public:
std::string m_vertexShaderFilePath;
    std::string m_frageShaderFilePath;
    unsigned int m_shaderID;
    std::map<std::string, int> uniforms;
    void createShader();
    static std::string readShaderFile(const char* path);
    static GLuint compileShader(GLuint type, std::string& source);
public:
    Shader(const std::string& vs_path, const std::string& fs_path);
    ~Shader();

    void bind() const;
    static void unbind() ;
    void setUniform4f(std::string &name, float v1, float v2, float v3, float v4);
    static void reportError();
    GLuint getProgramID() { return m_shaderID; }
};

#endif