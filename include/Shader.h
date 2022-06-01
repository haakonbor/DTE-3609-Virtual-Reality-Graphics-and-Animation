#pragma once

#include <string>
#include <unordered_map>

#include "../../glm-master/glm/glm.hpp"

class Shader {
private:
    std::string m_VertexShaderFilePath;
    std::string m_FragmentShaderFilePath;
    unsigned int m_RendererID;
    std::unordered_map<std::string, int> m_UniformLocationCache;
    std::string m_VertexShaderSource;
    std::string m_FragmentShaderSource;

public:
    Shader(const std::string& vertexShaderFilepath, const std::string& fragmentShaderFilepath);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    void SetUniform1i(const std::string& name, int value);
    void SetUniform3f(const std::string& name, float v0, float v1, float v2);
    void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
    void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);

private:
    int GetUniformLocation(const std::string& name);
    unsigned int CompileShader(unsigned int type, const std::string& source);
    std::string ParseShader(const std::string& filepath);
    unsigned int CreateShader(const std::string& vertexShaderCode, const std::string& fragmentShaderCode);
};
