#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <memory>
#include <string>

namespace lumin {

/**
 * Mesh - represents geometry data (vertices, indices, etc.)
 */
class Mesh {
public:
    struct Vertex {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texCoord;
    };

    Mesh();
    ~Mesh();

    void setVertices(const std::vector<Vertex>& vertices);
    void setIndices(const std::vector<uint32_t>& indices);
    
    const std::vector<Vertex>& getVertices() const { return vertices_; }
    const std::vector<uint32_t>& getIndices() const { return indices_; }
    
    // Helper methods
    static std::shared_ptr<Mesh> createCube(float size = 1.0f);
    static std::shared_ptr<Mesh> createSphere(float radius = 1.0f, int segments = 32);
    static std::shared_ptr<Mesh> createPlane(float width = 1.0f, float height = 1.0f);

private:
    std::vector<Vertex> vertices_;
    std::vector<uint32_t> indices_;
};

/**
 * Texture - image data for rendering
 */
class Texture {
public:
    Texture();
    ~Texture();

    bool loadFromFile(const std::string& path);
    uint32_t getID() const { return textureID_; }
    int getWidth() const { return width_; }
    int getHeight() const { return height_; }

private:
    uint32_t textureID_;
    int width_;
    int height_;
};

/**
 * Material - defines visual properties of objects
 */
class Material {
public:
    Material();
    
    void setDiffuseTexture(std::shared_ptr<Texture> texture);
    void setNormalTexture(std::shared_ptr<Texture> texture);
    void setAlbedo(const glm::vec3& color) { albedo_ = color; }
    void setMetallic(float value) { metallic_ = value; }
    void setRoughness(float value) { roughness_ = value; }

    std::shared_ptr<Texture> getDiffuseTexture() const { return diffuseTexture_; }
    std::shared_ptr<Texture> getNormalTexture() const { return normalTexture_; }
    glm::vec3 getAlbedo() const { return albedo_; }
    float getMetallic() const { return metallic_; }
    float getRoughness() const { return roughness_; }

private:
    std::shared_ptr<Texture> diffuseTexture_;
    std::shared_ptr<Texture> normalTexture_;
    glm::vec3 albedo_;
    float metallic_;
    float roughness_;
};

} // namespace lumin
