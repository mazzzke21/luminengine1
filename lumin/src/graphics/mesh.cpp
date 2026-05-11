#include "graphics/mesh.h"
#include <glm/gtc/constants.hpp>
#include <cmath>

namespace lumin {

Mesh::Mesh() {
}

Mesh::~Mesh() {
    vertices_.clear();
    indices_.clear();
}

void Mesh::setVertices(const std::vector<Vertex>& vertices) {
    vertices_ = vertices;
}

void Mesh::setIndices(const std::vector<uint32_t>& indices) {
    indices_ = indices;
}

std::shared_ptr<Mesh> Mesh::createCube(float size) {
    auto mesh = std::make_shared<Mesh>();
    float half = size / 2.0f;

    std::vector<Vertex> vertices = {
        // Front face
        {{-half, -half,  half}, {0, 0, 1}, {0, 0}},
        {{ half, -half,  half}, {0, 0, 1}, {1, 0}},
        {{ half,  half,  half}, {0, 0, 1}, {1, 1}},
        {{-half,  half,  half}, {0, 0, 1}, {0, 1}},
        // Back face
        {{-half, -half, -half}, {0, 0, -1}, {1, 0}},
        {{-half,  half, -half}, {0, 0, -1}, {1, 1}},
        {{ half,  half, -half}, {0, 0, -1}, {0, 1}},
        {{ half, -half, -half}, {0, 0, -1}, {0, 0}},
        // Top face
        {{-half,  half, -half}, {0, 1, 0}, {0, 1}},
        {{-half,  half,  half}, {0, 1, 0}, {0, 0}},
        {{ half,  half,  half}, {0, 1, 0}, {1, 0}},
        {{ half,  half, -half}, {0, 1, 0}, {1, 1}},
        // Bottom face
        {{-half, -half, -half}, {0, -1, 0}, {1, 1}},
        {{ half, -half, -half}, {0, -1, 0}, {0, 1}},
        {{ half, -half,  half}, {0, -1, 0}, {0, 0}},
        {{-half, -half,  half}, {0, -1, 0}, {1, 0}},
        // Right face
        {{ half, -half, -half}, {1, 0, 0}, {1, 0}},
        {{ half,  half, -half}, {1, 0, 0}, {1, 1}},
        {{ half,  half,  half}, {1, 0, 0}, {0, 1}},
        {{ half, -half,  half}, {1, 0, 0}, {0, 0}},
        // Left face
        {{-half, -half, -half}, {-1, 0, 0}, {0, 0}},
        {{-half, -half,  half}, {-1, 0, 0}, {1, 0}},
        {{-half,  half,  half}, {-1, 0, 0}, {1, 1}},
        {{-half,  half, -half}, {-1, 0, 0}, {0, 1}},
    };

    std::vector<uint32_t> indices = {
        0, 1, 2, 2, 3, 0,       // Front
        4, 6, 5, 6, 7, 4,       // Back
        8, 9, 10, 10, 11, 8,    // Top
        12, 14, 13, 14, 15, 12, // Bottom
        16, 17, 18, 18, 19, 16, // Right
        20, 22, 21, 22, 23, 20  // Left
    };

    mesh->setVertices(vertices);
    mesh->setIndices(indices);
    return mesh;
}

std::shared_ptr<Mesh> Mesh::createSphere(float radius, int segments) {
    auto mesh = std::make_shared<Mesh>();
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

    float pi = glm::pi<float>();

    for (int i = 0; i <= segments; ++i) {
        float phi = pi * i / segments;
        float sinPhi = std::sin(phi);
        float cosPhi = std::cos(phi);

        for (int j = 0; j <= segments; ++j) {
            float theta = 2 * pi * j / segments;
            float sinTheta = std::sin(theta);
            float cosTheta = std::cos(theta);

            glm::vec3 pos(radius * sinPhi * cosTheta,
                         radius * cosPhi,
                         radius * sinPhi * sinTheta);
            glm::vec3 normal = glm::normalize(pos);
            glm::vec2 texCoord(j / (float)segments, i / (float)segments);

            vertices.push_back({pos, normal, texCoord});
        }
    }

    for (int i = 0; i < segments; ++i) {
        for (int j = 0; j < segments; ++j) {
            uint32_t first = (i * (segments + 1)) + j;
            uint32_t second = first + segments + 1;

            indices.push_back(first);
            indices.push_back(second);
            indices.push_back(first + 1);

            indices.push_back(second);
            indices.push_back(second + 1);
            indices.push_back(first + 1);
        }
    }

    mesh->setVertices(vertices);
    mesh->setIndices(indices);
    return mesh;
}

std::shared_ptr<Mesh> Mesh::createPlane(float width, float height) {
    auto mesh = std::make_shared<Mesh>();
    float hw = width / 2.0f;
    float hh = height / 2.0f;

    std::vector<Vertex> vertices = {
        {{-hw, 0, -hh}, {0, 1, 0}, {0, 1}},
        {{ hw, 0, -hh}, {0, 1, 0}, {1, 1}},
        {{ hw, 0,  hh}, {0, 1, 0}, {1, 0}},
        {{-hw, 0,  hh}, {0, 1, 0}, {0, 0}},
    };

    std::vector<uint32_t> indices = {0, 1, 2, 2, 3, 0};

    mesh->setVertices(vertices);
    mesh->setIndices(indices);
    return mesh;
}

Texture::Texture()
    : textureID_(0), width_(0), height_(0) {
}

Texture::~Texture() {
    // glDeleteTextures(1, &textureID_);
}

bool Texture::loadFromFile(const std::string& path) {
    // Load texture using SOIL or stb_image
    return true;
}

Material::Material()
    : albedo_(0.8f), metallic_(0.0f), roughness_(0.5f) {
}

void Material::setDiffuseTexture(std::shared_ptr<Texture> texture) {
    diffuseTexture_ = texture;
}

void Material::setNormalTexture(std::shared_ptr<Texture> texture) {
    normalTexture_ = texture;
}

} // namespace lumin
