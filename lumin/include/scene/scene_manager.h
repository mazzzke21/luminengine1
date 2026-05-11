#pragma once

#include "ecs/entity_manager.h"
#include <vector>
#include <memory>
#include <string>

namespace lumin {

/**
 * Scene - represents a game level or state
 * Contains a collection of entities and manages their lifetime
 */
class Scene {
public:
    explicit Scene(const std::string& name);
    ~Scene();

    const std::string& getName() const { return name_; }

    // Entity management
    Entity* createEntity();
    bool destroyEntity(EntityID id);
    Entity* getEntity(EntityID id);

    // Updates
    void update(float deltaTime);
    void fixedUpdate(float fixedDeltaTime);

    // Scene lifecycle
    virtual void onLoad() {}
    virtual void onUnload() {}
    virtual void onUpdate(float deltaTime) {}

protected:
    EntityManager entityManager_;
    std::string name_;
};

/**
 * Scene Manager - manages multiple scenes and scene transitions
 */
class SceneManager {
public:
    SceneManager();
    ~SceneManager();

    // Scene management
    Scene* createScene(const std::string& name);
    bool loadScene(const std::string& name);
    bool unloadScene(const std::string& name);
    Scene* getActiveScene() const { return activeScene_; }
    Scene* getScene(const std::string& name);

    // Updates
    void update(float deltaTime);

private:
    std::vector<std::unique_ptr<Scene>> scenes_;
    Scene* activeScene_;
};

} // namespace lumin
