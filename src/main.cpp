#include "config.h"

struct Engine {
    GLFWwindow* window;
    int WIDTH = 800;
    int HEIGHT = 600;

    /*creates the window*/
    Engine() {
        //wake up GLFW
        if (!glfwInit()) {
            std::cout << "GLFW didn't start" << std::endl;
            exit(EXIT_FAILURE);
        }

        //ask the operating system for a window
        window = glfwCreateWindow(WIDTH, HEIGHT, "Hello World!", nullptr, nullptr);

        //checks if the window exists
        if (!window) {
            std::cout << "Window Failed" << std::endl;
            glfwTerminate();
            exit(EXIT_FAILURE);
        }

        //makes all openGL calls go to that window
        glfwMakeContextCurrent(window);
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

        //centers the origin
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-WIDTH / 2.0, WIDTH / 2.0, -HEIGHT / 2.0, HEIGHT / 2.0, -1.0, 1.0);
    }

    /*shuts down glfw*/
    ~Engine() {
        glfwTerminate();
    }

    void run() {
        while (!glfwWindowShouldClose(window)) {
            glClear(GL_COLOR_BUFFER_BIT);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();

            draw();

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    void draw() {
        //draw everything here
    }

};

int main(){
    Engine engine;
    engine.run();
    return 0;
}