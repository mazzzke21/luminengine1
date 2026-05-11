#pragma once

#include "ecs/entity.h"
#include <glm/glm.hpp>
#include <memory>

namespace lumin {

class Texture;
class Material;
class Mesh;

/**
 * Renderer Component - handles rendering of 3D geometry
 */
class MeshRenderer : public Component {
public:
    MeshRenderer();
    
    void setMesh(std::shared_ptr<Mesh> mesh) { mesh_ = mesh; }
    void setMaterial(std::shared_ptr<Material> material) { material_ = material; }
    
    std::shared_ptr<Mesh> getMesh() const { return mesh_; }
    std::shared_ptr<Material> getMaterial() const { return material_; }

private:
    std::shared_ptr<Mesh> mesh_;
    std::shared_ptr<Material> material_;
};

/**
 * Camera Component - defines view into the scene
 */
class Camera : public Component {
public:
    Camera();
    
    void setPerspective(float fov, float aspectRatio, float nearPlane, float farPlane);
    void setOrthographic(float left, float right, float bottom, float top, float nearPlane, float farPlane);
    
    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix() const;
    glm::mat4 getViewProjectionMatrix() const;

    float getFOV() const { return fov_; }
    float getAspectRatio() const { return aspectRatio_; }
    float getNearPlane() const { return nearPlane_; }
    float getFarPlane() const { return farPlane_; }

private:
    glm::mat4 projectionMatrix_;
    bool isPerspective_;
    float fov_;
    float aspectRatio_;
    float nearPlane_;
    float farPlane_;
};

/**
 * Light Component - illuminates the scene
 */
class Light : public Component {
public:
    enum class LightType { Directional, Point, Spot };

    Light(LightType type);
    
    LightType getType() const { return type_; }
    void setColor(const glm::vec3& color) { color_ = color; }
    void setIntensity(float intensity) { intensity_ = intensity; }
    
    glm::vec3 getColor() const { return color_; }
    float getIntensity() const { return intensity_; }

private:
    LightType type_;
    glm::vec3 color_;
    float intensity_;
};

} // namespace lumin
