#ifndef SHADER_H
#define SHADER_H

#include <GLAD/glad.h> // include glad to get all the required OpenGL headers

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
    // the program ID
    unsigned int ID;

    // constructor reads and builds the shader
    Shader(const char *vertexPath, const char *fragmentPath);
    ~Shader();

    // Use / activate the shader program
    void Use();

    // Uniform utils
    void SetBool(const std::string &name, bool value) const;
    void SetInt(const std::string &name, int value) const;
    void SetFloat(const std::string &name, float value) const;
};

#endif
