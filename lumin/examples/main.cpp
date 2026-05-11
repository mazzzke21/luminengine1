#include "engine.h"
#include <iostream>

using namespace lumin;

/**
 * Example game demonstrating the Lumin Engine
 * This shows basic usage of the engine for a simple 3D game
 */
class ExampleGame {
public:
    ExampleGame() : engine_(nullptr) {
    }

    bool initialize() {
        engine_ = std::make_unique<Engine>();
        
        if (!engine_->initialize(1280, 720, "Lumin Engine - Example Game")) {
            std::cerr << "Failed to initialize engine" << std::endl;
            return false;
        }

        setupScene();
        return true;
    }

    void run() {
        engine_->run();
    }

private:
    std::unique_ptr<Engine> engine_;

    void setupScene() {
        // Create a game scene
        Scene* mainScene = engine_->getSceneManager().createScene("MainScene");
        
        // Load the scene
        engine_->getSceneManager().loadScene("MainScene");

        // Create a camera
        Entity* cameraEntity = mainScene->createEntity();
        auto transform = cameraEntity->addComponent<Transform>();
        transform->setPosition(glm::vec3(0.0f, 5.0f, 10.0f));
        auto camera = cameraEntity->addComponent<Camera>();
        camera->setPerspective(45.0f, 16.0f / 9.0f, 0.1f, 1000.0f);

        // Create a player entity with physics
        Entity* playerEntity = mainScene->createEntity();
        auto playerTransform = playerEntity->addComponent<Transform>();
        playerTransform->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
        auto rigidBody = playerEntity->addComponent<RigidBody>(RigidBody::BodyType::Dynamic);
        rigidBody->setMass(1.0f);
        auto collider = playerEntity->addComponent<Collider>(Collider::ShapeType::Box);
        collider->setSize(glm::vec3(1.0f, 1.0f, 1.0f));

        // Create a ground plane
        Entity* groundEntity = mainScene->createEntity();
        auto groundTransform = groundEntity->addComponent<Transform>();
        groundTransform->setPosition(glm::vec3(0.0f, -5.0f, 0.0f));
        groundTransform->setScale(glm::vec3(100.0f, 1.0f, 100.0f));
        auto groundRigidBody = groundEntity->addComponent<RigidBody>(RigidBody::BodyType::Static);
        auto groundCollider = groundEntity->addComponent<Collider>(Collider::ShapeType::Box);
        groundCollider->setSize(glm::vec3(100.0f, 1.0f, 100.0f));

        // Create a light
        Entity* lightEntity = mainScene->createEntity();
        auto lightTransform = lightEntity->addComponent<Transform>();
        lightTransform->setPosition(glm::vec3(10.0f, 10.0f, 10.0f));
        auto light = lightEntity->addComponent<Light>(Light::LightType::Directional);
        light->setColor(glm::vec3(1.0f));
        light->setIntensity(1.0f);

        std::cout << "Scene setup complete. Created camera, player, ground, and light." << std::endl;
    }
};

int main() {
    ExampleGame game;
    
    if (!game.initialize()) {
        std::cerr << "Failed to initialize game" << std::endl;
        return 1;
    }

    game.run();

    return 0;
}
