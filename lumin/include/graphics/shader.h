#pragma once

#include <string>
#include <glm/glm.hpp>

namespace lumin {

/**
 * Shader - represents vertex and fragment shaders
 */
class Shader {
public:
    Shader();
    ~Shader();

    bool loadFromFile(const std::string& vertexPath, const std::string& fragmentPath);
    bool loadFromString(const std::string& vertexSource, const std::string& fragmentSource);

    void use() const;
    void unuse() const;

    // Uniforms
    void setUniformMatrix4f(const std::string& name, const glm::mat4& matrix);
    void setUniformVector3f(const std::string& name, const glm::vec3& vec);
    void setUniformVector4f(const std::string& name, const glm::vec4& vec);
    void setUniformFloat(const std::string& name, float value);
    void setUniformInt(const std::string& name, int value);

    uint32_t getProgramID() const { return programID_; }

private:
    uint32_t programID_;
    
    uint32_t compileShader(uint32_t type, const std::string& source);
    std::string readFile(const std::string& path);
};

} // namespace lumin
