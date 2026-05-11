#pragma once

#include "ecs/entity.h"
#include <glm/glm.hpp>

namespace lumin {

/**
 * RigidBody Component - adds physics simulation to entities
 */
class RigidBody : public Component {
public:
    enum class BodyType { Static, Dynamic, Kinematic };

    RigidBody(BodyType type = BodyType::Dynamic);

    void setMass(float mass);
    void setVelocity(const glm::vec3& velocity);
    void setAngularVelocity(const glm::vec3& angularVel);
    void applyForce(const glm::vec3& force);
    void applyTorque(const glm::vec3& torque);
    void applyImpulse(const glm::vec3& impulse);

    float getMass() const { return mass_; }
    glm::vec3 getVelocity() const { return velocity_; }
    glm::vec3 getAngularVelocity() const { return angularVelocity_; }
    BodyType getBodyType() const { return bodyType_; }

    // Physics material
    void setFriction(float friction) { friction_ = friction; }
    void setRestitution(float restitution) { restitution_ = restitution; }
    float getFriction() const { return friction_; }
    float getRestitution() const { return restitution_; }

private:
    BodyType bodyType_;
    float mass_;
    glm::vec3 velocity_;
    glm::vec3 angularVelocity_;
    glm::vec3 acceleration_;
    float friction_;
    float restitution_;
};

/**
 * Collider Component - defines collision geometry
 */
class Collider : public Component {
public:
    enum class ShapeType { Box, Sphere, Capsule, Mesh };

    Collider(ShapeType shape = ShapeType::Box);

    ShapeType getShapeType() const { return shapeType_; }
    void setSize(const glm::vec3& size);
    void setRadius(float radius);
    glm::vec3 getSize() const { return size_; }
    float getRadius() const { return radius_; }

    // Collision events
    bool isTrigger() const { return isTrigger_; }
    void setIsTrigger(bool trigger) { isTrigger_ = trigger; }

private:
    ShapeType shapeType_;
    glm::vec3 size_;
    float radius_;
    bool isTrigger_;
};

} // namespace lumin
