#include "config.h"
#include "mesh.h"

unsigned int make_module(const std::string& filepath, unsigned int module_type);
unsigned int make_shader(const std::string& vertex_filepath, const std::string& fragment_filepath);

struct Triangle {
    Mesh* mesh;
    std::vector<float> baseVertices;
    std::vector<float> vertices;
    
    Triangle() {
        baseVertices: 
            baseVertices = {
                -0.5f, -0.5f,  0.0f,  1.0f, 0.0f, 0.0f, 1.0f,
                0.5f, -0.5f,  0.0f,  0.0f, 1.0f, 0.0f, 1.0f,
                0.0f,  0.5f,  0.0f,  0.0f, 0.0f, 1.0f, 1.0f
            };
        
        vertices:
            vertices = baseVertices;
        
        mesh = new Mesh(vertices);
    }

    ~Triangle() {
        delete mesh;
    }

    void draw() {
        mesh->draw();
    }

    void update() {
        double t = glfwGetTime();
        double s = 0.125 * sin(t);
        float y = (float) s;

        vertices[1] = baseVertices[1] + y;
        vertices[8] = baseVertices[8] + y;
        vertices[15] = baseVertices[15] + y;

        mesh->update(vertices);
    }
};

struct Engine {
    GLFWwindow* window;
    Triangle* triangle;

    int WIDTH = 800;
    int HEIGHT = 600;
    unsigned int shader;

    Engine() {
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
            "../src/shaders/vertex.txt",
            "../src/shaders/fragment.txt"
        );

        //you won't believe this but this makes a triangle!
        triangle = new Triangle();

    }

    ~Engine() {
        //this deletes the triangle... so crazy!
        delete triangle;

        glDeleteProgram(shader);
        glfwTerminate();
    }

    void run() {
        while (!glfwWindowShouldClose(window)) {
            glClear(GL_COLOR_BUFFER_BIT);
            glUseProgram(shader);

            draw(); //completely useless but clean... maybe?

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    void draw() {
        triangle->draw(); //this? you guessed it. it draws the triangle.
        triangle->update(); //and this updates the triangle every frame!
    }
};


int main(){
    Engine engine;
    engine.run();
    return 0;
}


unsigned int make_shader(const std::string& vertex_filepath, const std::string& fragment_filepath) {

    std::vector<unsigned int> modules;
    modules.push_back(make_module(vertex_filepath, GL_VERTEX_SHADER));
    modules.push_back(make_module(fragment_filepath, GL_FRAGMENT_SHADER));

    unsigned int shader = glCreateProgram();
    for (unsigned int shaderModule : modules) {
        glAttachShader(shader, shaderModule);
    }
    glLinkProgram(shader);

    int success;
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[1024];
        glGetProgramInfoLog(shader, 1024, NULL, infoLog);
        std::cout << "Shader linking failed\n" << infoLog << std::endl;
    }

    for (unsigned int shaderModule : modules) {
        glDeleteShader(shaderModule);
    }

    return shader;
}

unsigned int make_module(const std::string& filepath, unsigned int module_type) {

    std::ifstream file;
    std::stringstream bufferedLines;
    std::string line;

    //writes the file contents to a buffer
    file.open(filepath);
    while (std::getline(file, line)) {
        bufferedLines << line << "\n";
    }

    std::string shaderSource = bufferedLines.str(); //copies the buffer as a string
    const char* shaderSrc = shaderSource.c_str(); //pointer to the string
    bufferedLines.str(""); //clears the buffer
    file.close();

    //compiles the shader
    unsigned int shaderModule = glCreateShader(module_type);
    glShaderSource(shaderModule, 1, &shaderSrc, NULL);
    glCompileShader(shaderModule);

    //checks if the shader compilation worked
    int success;
    glGetShaderiv(shaderModule, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[1024];
        glGetShaderInfoLog(shaderModule, 1024, NULL, infoLog);
        std::cout << "Shader compilation failed\n" << infoLog << std::endl;
    }

    return shaderModule;
}