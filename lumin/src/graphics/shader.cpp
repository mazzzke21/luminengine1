#include "graphics/shader.h"
#include <fstream>
#include <sstream>
#include <iostream>

namespace lumin {

Shader::Shader()
    : programID_(0) {
}

Shader::~Shader() {
    // glDeleteProgram(programID_);
}

bool Shader::loadFromFile(const std::string& vertexPath, const std::string& fragmentPath) {
    std::string vertexSource = readFile(vertexPath);
    std::string fragmentSource = readFile(fragmentPath);
    return loadFromString(vertexSource, fragmentSource);
}

bool Shader::loadFromString(const std::string& vertexSource, const std::string& fragmentSource) {
    uint32_t vertexShader = compileShader(0x8B31, vertexSource);  // GL_VERTEX_SHADER
    if (vertexShader == 0) return false;

    uint32_t fragmentShader = compileShader(0x8B30, fragmentSource);  // GL_FRAGMENT_SHADER
    if (fragmentShader == 0) return false;

    // programID_ = glCreateProgram();
    // glAttachShader(programID_, vertexShader);
    // glAttachShader(programID_, fragmentShader);
    // glLinkProgram(programID_);

    // glDeleteShader(vertexShader);
    // glDeleteShader(fragmentShader);

    return true;
}

void Shader::use() const {
    // glUseProgram(programID_);
}

void Shader::unuse() const {
    // glUseProgram(0);
}

void Shader::setUniformMatrix4f(const std::string& name, const glm::mat4& matrix) {
    // GLint loc = glGetUniformLocation(programID_, name.c_str());
    // glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::setUniformVector3f(const std::string& name, const glm::vec3& vec) {
    // GLint loc = glGetUniformLocation(programID_, name.c_str());
    // glUniform3fv(loc, 1, glm::value_ptr(vec));
}

void Shader::setUniformVector4f(const std::string& name, const glm::vec4& vec) {
    // GLint loc = glGetUniformLocation(programID_, name.c_str());
    // glUniform4fv(loc, 1, glm::value_ptr(vec));
}

void Shader::setUniformFloat(const std::string& name, float value) {
    // GLint loc = glGetUniformLocation(programID_, name.c_str());
    // glUniform1f(loc, value);
}

void Shader::setUniformInt(const std::string& name, int value) {
    // GLint loc = glGetUniformLocation(programID_, name.c_str());
    // glUniform1i(loc, value);
}

uint32_t Shader::compileShader(uint32_t type, const std::string& source) {
    // uint32_t shader = glCreateShader(type);
    // const char* src = source.c_str();
    // glShaderSource(shader, 1, &src, nullptr);
    // glCompileShader(shader);
    // return shader;
    return 0;
}

std::string Shader::readFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Failed to open shader file: " << path << std::endl;
        return "";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

} // namespace lumin
