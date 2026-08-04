//
// Created by Citarlia on 2026/7/30.
//

#ifndef OPENGLBASIC_FPSCOUNTER_H
#define OPENGLBASIC_FPSCOUNTER_H
#include <iostream>
#include "GLFW/glfw3.h"

class FPSCounter {
public:
    FPSCounter(float updateInterval = 1.0f)
        : m_updateInterval(updateInterval), m_lastTime(glfwGetTime()), m_frameCount(0), m_fps(0.0f) {}

    void tick() {
        double currentTime = glfwGetTime();
        m_frameCount++;

        if (currentTime - m_lastTime >= m_updateInterval) {
            m_fps = m_frameCount / (currentTime - m_lastTime);
            std::cout << "FPS: " << m_fps << std::endl;
            m_lastTime = currentTime;
            m_frameCount = 0;
        }
    }

    float getFPS() const { return m_fps; }

private:
    float m_updateInterval;
    double m_lastTime;
    int m_frameCount;
    float m_fps;
};
#endif //OPENGLBASIC_FPSCOUNTER_H
