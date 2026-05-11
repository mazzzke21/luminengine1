#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "ecs/entity.h"

namespace lumin {

/**
 * Transform Component - represents position, rotation, and scale
 * Essential component for all spatial entities
 */
class Transform : public Component {
public:
    Transform();
    explicit Transform(const glm::vec3& position);
    
    // Position
    void setPosition(const glm::vec3& pos);
    glm::vec3 getPosition() const { return position_; }
    void translate(const glm::vec3& offset);

    // Rotation
    void setRotation(const glm::quat& rot);
    void setEulerAngles(const glm::vec3& angles);
    glm::quat getRotation() const { return rotation_; }
    glm::vec3 getEulerAngles() const;
    void rotate(const glm::quat& rot);

    // Scale
    void setScale(const glm::vec3& scale);
    glm::vec3 getScale() const { return scale_; }

    // Direction vectors
    glm::vec3 getForward() const;
    glm::vec3 getRight() const;
    glm::vec3 getUp() const;

    // Transformation matrix
    glm::mat4 getMatrix() const;
    glm::mat4 getInverseMatrix() const;

    // Hierarchy
    void setParent(Transform* parent);
    Transform* getParent() const { return parent_; }
    const std::vector<Transform*>& getChildren() const { return children_; }

private:
    glm::vec3 position_;
    glm::quat rotation_;
    glm::vec3 scale_;
    Transform* parent_;
    std::vector<Transform*> children_;
    
    mutable glm::mat4 cachedMatrix_;
    mutable bool matrixDirty_;
};

} // namespace lumin
