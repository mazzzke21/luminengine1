#include "physics/physics_engine.h"

namespace lumin {

PhysicsEngine::PhysicsEngine()
    : gravity_(0.0f, -9.81f, 0.0f), dynamicsWorld_(nullptr) {
}

PhysicsEngine::~PhysicsEngine() {
    shutdown();
}

void PhysicsEngine::initialize() {
    // Initialize Bullet Physics
    // btCollisionConfiguration* collisionConfig = new btDefaultCollisionConfiguration();
    // btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfig);
    // btBroadphaseInterface* broadphase = new btDbvtBroadphase();
    // btConstraintSolver* solver = new btSequentialImpulseConstraintSolver();
    // dynamicsWorld_ = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfig);
    // ((btDiscreteDynamicsWorld*)dynamicsWorld_)->setGravity(btVector3(gravity_.x, gravity_.y, gravity_.z));
}

void PhysicsEngine::shutdown() {
    // Cleanup Bullet Physics
}

void PhysicsEngine::update(float deltaTime) {
    // Step simulation
    // if (dynamicsWorld_) {
    //     ((btDiscreteDynamicsWorld*)dynamicsWorld_)->stepSimulation(deltaTime, 10);
    // }
}

bool PhysicsEngine::raycast(const glm::vec3& origin, const glm::vec3& direction, float maxDistance) {
    return false;
}

} // namespace lumin
