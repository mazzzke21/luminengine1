#include "core/transform.h"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

namespace lumin {

Transform::Transform()
    : position_(0.0f), rotation_(glm::quat(1.0f, 0.0f, 0.0f, 0.0f)), 
      scale_(1.0f), parent_(nullptr), matrixDirty_(true) {
}

Transform::Transform(const glm::vec3& position)
    : position_(position), rotation_(glm::quat(1.0f, 0.0f, 0.0f, 0.0f)),
      scale_(1.0f), parent_(nullptr), matrixDirty_(true) {
}

void Transform::setPosition(const glm::vec3& pos) {
    position_ = pos;
    matrixDirty_ = true;
}

void Transform::translate(const glm::vec3& offset) {
    position_ += offset;
    matrixDirty_ = true;
}

void Transform::setRotation(const glm::quat& rot) {
    rotation_ = rot;
    matrixDirty_ = true;
}

void Transform::setEulerAngles(const glm::vec3& angles) {
    rotation_ = glm::quat(angles);
    matrixDirty_ = true;
}

glm::vec3 Transform::getEulerAngles() const {
    return glm::eulerAngles(rotation_);
}

void Transform::rotate(const glm::quat& rot) {
    rotation_ = rot * rotation_;
    matrixDirty_ = true;
}

void Transform::setScale(const glm::vec3& s) {
    scale_ = s;
    matrixDirty_ = true;
}

glm::vec3 Transform::getForward() const {
    return glm::normalize(rotation_ * glm::vec3(0.0f, 0.0f, -1.0f));
}

glm::vec3 Transform::getRight() const {
    return glm::normalize(rotation_ * glm::vec3(1.0f, 0.0f, 0.0f));
}

glm::vec3 Transform::getUp() const {
    return glm::normalize(rotation_ * glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::mat4 Transform::getMatrix() const {
    if (matrixDirty_) {
        glm::mat4 mat = glm::mat4_cast(rotation_);
        mat = glm::translate(mat, position_);
        mat = glm::scale(mat, scale_);
        cachedMatrix_ = mat;
        matrixDirty_ = false;
    }
    return cachedMatrix_;
}

glm::mat4 Transform::getInverseMatrix() const {
    return glm::inverse(getMatrix());
}

void Transform::setParent(Transform* parent) {
    parent_ = parent;
    if (parent) {
        auto it = std::find(parent_->children_.begin(), parent_->children_.end(), this);
        if (it == parent_->children_.end()) {
            parent_->children_.push_back(this);
        }
    }
}

} // namespace lumin
