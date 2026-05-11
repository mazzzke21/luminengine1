#pragma once

#include <glm/glm.hpp>
#include <memory>

namespace lumin {

/**
 * Physics Engine - handles all physics simulation
 */
class PhysicsEngine {
public:
    PhysicsEngine();
    ~PhysicsEngine();

    void initialize();
    void shutdown();

    void update(float deltaTime);

    // Physics settings
    void setGravity(const glm::vec3& gravity) { gravity_ = gravity; }
    glm::vec3 getGravity() const { return gravity_; }

    // Raycasting
    bool raycast(const glm::vec3& origin, const glm::vec3& direction, float maxDistance);

private:
    glm::vec3 gravity_;
    void* dynamicsWorld_;  // btDynamicsWorld*
};

} // namespace lumin
