#pragma once

#include "ecs/entity_manager.h"
#include "graphics/renderer.h"
#include "physics/physics_engine.h"
#include "audio/audio_engine.h"
#include "input/input_manager.h"
#include "scene/scene_manager.h"
#include <memory>
#include <chrono>

namespace lumin {

/**
 * Core game engine class that manages all subsystems
 */
class Engine {
public:
    Engine();
    ~Engine();

    // Initialization and shutdown
    bool initialize(int width, int height, const char* title);
    void shutdown();

    // Main game loop
    void run();
    void update(float deltaTime);
    void render();

    // Getters for subsystems
    EntityManager& getEntityManager() { return *entityManager_; }
    Renderer& getRenderer() { return *renderer_; }
    PhysicsEngine& getPhysicsEngine() { return *physicsEngine_; }
    AudioEngine& getAudioEngine() { return *audioEngine_; }
    InputManager& getInputManager() { return *inputManager_; }
    SceneManager& getSceneManager() { return *sceneManager_; }

    // Control
    void stop() { running_ = false; }
    bool isRunning() const { return running_; }

    // Time management
    float getDeltaTime() const { return deltaTime_; }
    float getTotalTime() const { return totalTime_; }

private:
    // Subsystems
    std::unique_ptr<EntityManager> entityManager_;
    std::unique_ptr<Renderer> renderer_;
    std::unique_ptr<PhysicsEngine> physicsEngine_;
    std::unique_ptr<AudioEngine> audioEngine_;
    std::unique_ptr<InputManager> inputManager_;
    std::unique_ptr<SceneManager> sceneManager_;

    // State
    bool running_;
    bool initialized_;
    float deltaTime_;
    float totalTime_;
    std::chrono::high_resolution_clock::time_point lastFrameTime_;

    void processEvents();
};

} // namespace lumin
