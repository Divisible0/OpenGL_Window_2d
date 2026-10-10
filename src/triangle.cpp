#include "triangle.h"

Triangle::Triangle() {

    baseVertices = {
        -0.5f, -0.5f,  0.0f,  1.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f,  0.0f,  0.0f, 1.0f, 0.0f, 1.0f,
        0.0f,  0.5f,  0.0f,  0.0f, 0.0f, 1.0f, 1.0f
    };

    vertices = baseVertices;

    mesh = new Mesh(vertices);
}

Triangle::~Triangle() {
    delete mesh;
}

void Triangle::draw() {
    mesh->draw();
}

void Triangle::update() {
    double t = glfwGetTime();
    double s = 0.125 * sin(t);
    float y = (float) s;

    vertices[1] = baseVertices[1] + y;
    vertices[8] = baseVertices[8] + y;
    vertices[15] = baseVertices[15] + y;

    mesh->update(vertices);
}