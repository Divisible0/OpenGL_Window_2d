#pragma once
#include "config.h"
#include "triangle.h"
#include "shader.h"

struct Engine {
    GLFWwindow* window;
    Triangle* triangle;

    int WIDTH = 800;
    int HEIGHT = 600;
    unsigned int shader;

    Engine();
    ~Engine();

    void run();
    void draw();
};