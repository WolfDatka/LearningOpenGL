#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

void FramebufferSizeCallback(GLFWwindow *window, int width, int height);
void ProcessInputs(GLFWwindow *window);
void Movement(GLFWwindow *window);
void MouseCallback(GLFWwindow *window, double xpos, double ypos);
void ScrollCallback(GLFWwindow *window, double xoffset, double yoffset);

#endif
