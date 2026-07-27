#include "Shader.h"

Shader::Shader(const std::string& vs_path,const std::string& fs_path) : m_vertexShaderFilePath(vs_path),
            m_frageShaderFilePath(fs_path), m_shaderID(0) {
    createShader();
}

Shader::~Shader() {
    glDeleteShader(m_shaderID);
}

void Shader::createShader() {
    std::string vsData = readShaderFile(m_vertexShaderFilePath.c_str());
    std::string fsData = readShaderFile(m_frageShaderFilePath.c_str());
    GLuint program = glCreateProgram();
    GLuint vs = compileShader(GL_VERTEX_SHADER, vsData);
    GLuint fs = compileShader(GL_FRAGMENT_SHADER, fsData);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);
    m_shaderID = program;
}

std::string Shader::readShaderFile(const char *path) {
    std::ifstream file;
    file.open(path);
    if (!file.is_open()) {
        std::cerr << "Read Error!\n";
        return {};
    }
    std::string data;
    std::string temp;
    while (std::getline(file, temp)) {
        temp += '\n';
        data += temp;
    }
    return data;
}

void Shader::bind() const {
    glUseProgram(m_shaderID);
}

GLuint Shader::compileShader(GLuint type, std::string &source) {
    GLuint id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    GLint rez = 0;
    glGetShaderiv(id, GL_COMPILE_STATUS, &rez);
    if (rez == GL_FALSE) {
        char *message = 0;
        int l = 0;

        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &l);

        if (l)
        {
            message = new char[l];

            glGetShaderInfoLog(id, l, &l, message);

            message[l - 1] = 0;

            std::cout << source << ":\n" << message << "\n";

            delete[] message;

        }
        else
        {
            std::cout << source << ":\n" << "unknown error" << "\n";
        }

        glDeleteShader(id);

        id = 0;
        return id;
    }
    return id;
}

void Shader::unbind() {
    glUseProgram(0);
}

void Shader::setUniform4f(std::string& name, float v1, float v2, float v3, float v4) {
    int location = glGetUniformLocation(m_shaderID, name.c_str());
    if (location == -1) {
        std::cout << "Uniform error:" << name << "\n";
    }
    uniforms.emplace(name, location);
    glUniform4f(uniforms.find(name)->second, v1, v2, v3, v4);
}

void Shader::reportError() {
    GLuint errorCode = glGetError();
    if (errorCode != GL_NO_ERROR) {
        switch (errorCode) {
            case GL_INVALID_ENUM:
                std::cout << "GL_INVALID_ENUM\n";
                break;
                case GL_INVALID_VALUE:
                std::cout << "GL_INVALID_VALUE\n";
                break;
                case GL_INVALID_OPERATION:
                std::cout << "GL_INVALID_OPERATION\n";
                break;
                case GL_STACK_OVERFLOW:
                std::cout << "GL_STACK_OVERFLOW\n";
                break;
                case GL_STACK_UNDERFLOW:
                std::cout << "GL_STACK_UNDERFLOW\n";
                break;
                case GL_OUT_OF_MEMORY:
                std::cout << "GL_OUT_OF_MEMORY\n";
                break;
                default:
                std::cout << "Unknown error\n";
                break;
        }
        assert(false);
    }
}
