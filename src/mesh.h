#pragma once
#include "config.h"

struct Mesh {
    unsigned int VAO; 
    unsigned int VBO;
    int vertexCount;

    Mesh(const std::vector<float>& vertices);
    ~Mesh();

    void draw();
    void update(const std::vector<float>& vertices);
};