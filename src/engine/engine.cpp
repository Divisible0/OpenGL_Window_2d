#include "engine/engine.h"

Engine::Engine() {

    //wake up GLFW
    if (!glfwInit()) {
        std::cout << "GLFW didn't start" << std::endl;
        exit(EXIT_FAILURE);
    }

    //tell glfw what version and profile we are using (3.3, core profile)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    //ask the operating system for a window
    window = glfwCreateWindow(WIDTH, HEIGHT, "Hello World!", NULL, NULL);

    //checks if the window exists
    if (!window) {
        std::cout << "Window Failed" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    //makes all openGL calls go to that window
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
        
    if (glewInit() != GLEW_OK) {
        std::cout << "GLEW didn't start" << std::endl;
        exit(EXIT_FAILURE);
    }

    //gets the frame buffer info
    int fbWidth, fbHeight;
    glfwGetFramebufferSize(window, &fbWidth, &fbHeight);
    glViewport(0, 0, fbWidth, fbHeight);

    //sets the clear color
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);

    //specifies the shaders
    shader = make_shader(
        "../shaders/vertex.txt",
        "../shaders/fragment.txt"
    );

    //you won't believe this but this makes a triangle!
    triangle = new Triangle();
}

Engine::~Engine() {

    delete triangle;

    glDeleteProgram(shader);
    glfwTerminate(); 
}

void Engine::run() {
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shader);

        draw(); //completely useless but clean... er... maybe?

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void Engine::draw() {
    triangle->draw(); //this? you guessed it. it draws the triangle.
    triangle->update(); //and this updates the triangle every frame!
}