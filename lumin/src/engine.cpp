#include "engine.h"
#include <iostream>

namespace lumin {

Engine::Engine()
    : running_(false), initialized_(false), deltaTime_(0.0f), totalTime_(0.0f) {
}

Engine::~Engine() {
    if (initialized_) {
        shutdown();
    }
}

bool Engine::initialize(int width, int height, const char* title) {
    if (initialized_) {
        return false;
    }

    try {
        // Initialize subsystems
        entityManager_ = std::make_unique<EntityManager>();
        renderer_ = std::make_unique<Renderer>();
        physicsEngine_ = std::make_unique<PhysicsEngine>();
        audioEngine_ = std::make_unique<AudioEngine>();
        inputManager_ = std::make_unique<InputManager>();
        sceneManager_ = std::make_unique<SceneManager>();

        // Initialize renderer
        if (!renderer_->initialize(width, height, title)) {
            std::cerr << "Failed to initialize renderer" << std::endl;
            return false;
        }

        // Initialize physics
        physicsEngine_->initialize();

        // Initialize audio
        if (!audioEngine_->initialize()) {
            std::cerr << "Failed to initialize audio engine" << std::endl;
        }

        initialized_ = true;
        running_ = true;
        lastFrameTime_ = std::chrono::high_resolution_clock::now();

        std::cout << "Engine initialized successfully" << std::endl;
        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "Engine initialization failed: " << e.what() << std::endl;
        return false;
    }
}

void Engine::shutdown() {
    if (!initialized_) {
        return;
    }

    running_ = false;

    audioEngine_->shutdown();
    physicsEngine_->shutdown();
    renderer_->shutdown();

    entityManager_.reset();
    renderer_.reset();
    physicsEngine_.reset();
    audioEngine_.reset();
    inputManager_.reset();
    sceneManager_.reset();

    initialized_ = false;
    std::cout << "Engine shutdown complete" << std::endl;
}

void Engine::run() {
    if (!initialized_) {
        std::cerr << "Engine is not initialized" << std::endl;
        return;
    }

    while (running_ && !renderer_->shouldClose()) {
        auto currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> elapsed = currentTime - lastFrameTime_;
        deltaTime_ = elapsed.count();
        lastFrameTime_ = currentTime;

        processEvents();
        update(deltaTime_);
        render();

        totalTime_ += deltaTime_;
    }

    shutdown();
}

void Engine::update(float deltaTime) {
    inputManager_->update();
    sceneManager_->update(deltaTime);
    physicsEngine_->update(deltaTime);
    audioEngine_->update(deltaTime);
}

void Engine::render() {
    renderer_->beginFrame();
    renderer_->clear();
    // Render game objects
    renderer_->endFrame();
}

void Engine::processEvents() {
    // Handle input events from the renderer
    // This would be called by renderer to pass input events
}

} // namespace lumin
