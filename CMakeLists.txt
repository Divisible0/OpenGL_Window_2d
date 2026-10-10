cmake_minimum_required(VERSION 3.10.0)
project(2d_window VERSION 1.0.0)
set(dependencies OpenGL::GL glfw GLEW::GLEW)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

add_executable(2d_window src/main.cpp src/engine/engine.cpp src/engine/shader.cpp src/engine/mesh.cpp src/objects/triangle.cpp)
target_include_directories(2d_window PRIVATE src)
target_link_libraries(2d_window PRIVATE ${dependencies}) # links OpenGL, glfw3 and glew

add_custom_target(run COMMAND 2d_window DEPENDS 2d_window)