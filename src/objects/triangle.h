#pragma once
#include "config.h"
#include "engine/mesh.h"


struct Triangle {
    Mesh* mesh;
    std::vector<float> baseVertices;
    std::vector<float> vertices;

    Triangle();
    ~Triangle();

    void draw();
    void update();
};