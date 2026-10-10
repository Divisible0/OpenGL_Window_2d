#include "engine/shader.h"

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