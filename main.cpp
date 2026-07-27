#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

#include "Shader.h"
#include "Texture.h"

using namespace glm;

float vertexes[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
       -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
       -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

       -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
       -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
       -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

       -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
       -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
       -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
       -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
       -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
       -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

       -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
       -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
       -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

       -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
       -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
       -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

static vec3 cameraPos = vec3(0.0f, 0.0f, 1.0f);
static vec3 cameraTarget = vec3(0.0f, 0.0f, 0.0f);
static vec3 cameraDirection = normalize(cameraPos - cameraTarget);
static vec3 up = vec3(0.0f, 1.0f, 0.0f);
static vec3 cameraRight = normalize(cross(up, cameraDirection));
static vec3 cameraUp = cross(cameraDirection, cameraRight);
static vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
static float lastX = 400, lastY = 300;

void processInput(GLFWwindow *window)
{
    float deltaTime = 0.0f; // 当前帧与上一帧的时间差
    float lastFrame = 0.0f; // 上一帧的时间
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    float cameraSpeed = 0.001f * deltaTime;// adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        cameraPos.y += cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
        cameraPos.y -=  cameraSpeed;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    static bool firstMouse = true;
    if(firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    static float pitch = 0;
    static float yaw = 0;
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.05;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw   += xoffset;
    pitch += yoffset;

    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}

int main() {
#pragma region Frame
    if (!glfwInit()) {
        std::cerr << "GLFW初始化失败！\n";
        return 1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "openGL test", nullptr, nullptr);
    if (!window) {
        std::cerr << "窗口加载失败！\n";
        return 1;
    }

    glfwMakeContextCurrent(window); // 将窗口设为当前上下文
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        return 1;
    }
#pragma endregion

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexes), vertexes, GL_STATIC_DRAW);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(3*sizeof(float)));
    glBindVertexArray(0);

    Shader shader = Shader({"../resource/MyShader.vert"}, {"../resource/MyShader.frag"});
    shader.createShader();

    Texture texture = Texture({"../textures/sheri.png"}, 0);
    texture.setFilter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    texture.setWrapper(GL_TEXTURE_WRAP_S, GL_REPEAT);
    texture.setFilter(GL_TEXTURE_WRAP_T, GL_REPEAT);

    glClearColor(0.2, 0.3, 0.3, 1);
    glEnable(GL_DEPTH_TEST);
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shader.bind();
        glBindVertexArray(vao);
        GLuint u_location = glGetUniformLocation(shader.getProgramID(), "u_time");
        glUniform1f(u_location, glfwGetTime());

        texture.setSampler(shader.getProgramID(), {"sampler_"});
        // 模型矩阵
        mat4 model = rotate(mat4(1.0), radians(-55.0f), vec3(1.0, 1.0, 0.0));
        // 视图矩阵
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        processInput(window);
        glfwSetCursorPosCallback(window, mouse_callback);
        float radius = 10.0f;
        float camX = sin(glfwGetTime()) * radius;
        float camZ = cos(glfwGetTime()) * radius;
        mat4 view = lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        // 投影矩阵
        mat4 projection = perspective(radians(45.0f), float(800/600), 0.1f, 100.0f);
        // 传入矩阵
        GLuint modelLoc = glGetUniformLocation(shader.getProgramID(), "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));
        GLuint viewLoc = glGetUniformLocation(shader.getProgramID(), "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(view));
        GLuint projectionLoc = glGetUniformLocation(shader.getProgramID(), "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, value_ptr(projection));

        glDrawArrays(GL_TRIANGLES, 0 ,36);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}