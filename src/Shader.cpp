#include "../include/Shader.h"
#include "../include/GLErrorHandler.h"
#include "../../glm-master/glm/glm.hpp"
#include "../../glm-master/glm/gtc/type_ptr.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

Shader::Shader(const std::string& vertexShaderFilepath, const std::string& fragmentShaderFilepath)
    : m_VertexShaderFilePath(vertexShaderFilepath), m_FragmentShaderFilePath(fragmentShaderFilepath), m_RendererID(0)
{
    m_VertexShaderSource = ParseShader(vertexShaderFilepath);
    m_FragmentShaderSource = ParseShader(fragmentShaderFilepath);
    m_RendererID = CreateShader(m_VertexShaderSource, m_FragmentShaderSource);
}

Shader::~Shader()
{
    GLCall(glDeleteProgram(m_RendererID));
}

void Shader::Bind() const
{
    GLCall(glUseProgram(m_RendererID));
}

void Shader::Unbind() const
{
    GLCall(glUseProgram(0));
}

void Shader::SetUniform1i(const std::string& name, int value)
{
    GLCall(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniform3f(const std::string& name, float v0, float v1, float v2)
{
    GLCall(glUniform3f(GetUniformLocation(name), v0, v1, v2));
}
void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
    GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix)));
}

int Shader::GetUniformLocation(const std::string& name)
{
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end()) {
        return m_UniformLocationCache[name];
    }

    GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));

    if (location == -1) {
        std::cout << "Warning: uniform " << name << " does not exist!" << std::endl;
    }

    m_UniformLocationCache[name] = location;

    return location;
}

std::string Shader::ParseShader(const std::string& filepath) {
    std::ifstream stream(filepath);
    std::string line;
    std::string result;

    while (getline(stream, line)) {
        if (line.find("shader") != std::string::npos || line.find("//") != std::string::npos) {
            continue;
        }

        result += line + '\n';
    }

    return result;
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source) {
    // Get shader source code in string format and try to compile it
    GLCall(unsigned int id = glCreateShader(type));
    const char* src = source.c_str();
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));

    // Get compile result
    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));

    // Print potential compile errors
    if (result == GL_FALSE) {
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char* message = (char*)alloca(length * sizeof(char));
        GLCall(glGetShaderInfoLog(id, length, &length, message));
        std::cout << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << " shader compilation error." << std::endl;
        std::cout << message << std::endl;
        GLCall(glDeleteShader(id));
        return 0;
    }

    return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShaderCode, const std::string& fragmentShaderCode) {
    // Create empty program and compile shader source code
    GLCall(unsigned int program = glCreateProgram());
    unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, vertexShaderCode);
    unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderCode);

    // Attach and link shaders into program
    GLCall(glAttachShader(program, vertexShader));
    GLCall(glAttachShader(program, fragmentShader));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    // Delete original shaders (shaders already in program)
    GLCall(glDeleteShader(vertexShader));
    GLCall(glDeleteShader(fragmentShader));

    return program;
}
