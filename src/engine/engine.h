#pragma once
#include "config.h"
#include "objects/triangle.h"
#include "engine/shader.h"

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