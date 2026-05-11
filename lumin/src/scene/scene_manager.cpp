#include "scene/scene_manager.h"

namespace lumin {

// Scene implementation
Scene::Scene(const std::string& name)
    : name_(name) {
}

Scene::~Scene() {
    entityManager_.clear();
}

Entity* Scene::createEntity() {
    return entityManager_.createEntity();
}

bool Scene::destroyEntity(EntityID id) {
    return entityManager_.destroyEntity(id);
}

Entity* Scene::getEntity(EntityID id) {
    return entityManager_.getEntity(id);
}

void Scene::update(float deltaTime) {
    entityManager_.update(deltaTime);
    onUpdate(deltaTime);
}

void Scene::fixedUpdate(float fixedDeltaTime) {
}

// SceneManager implementation
SceneManager::SceneManager()
    : activeScene_(nullptr) {
}

SceneManager::~SceneManager() {
    scenes_.clear();
}

Scene* SceneManager::createScene(const std::string& name) {
    auto scene = std::make_unique<Scene>(name);
    Scene* ptr = scene.get();
    scenes_.push_back(std::move(scene));
    return ptr;
}

bool SceneManager::loadScene(const std::string& name) {
    Scene* scene = getScene(name);
    if (!scene) {
        return false;
    }
    if (activeScene_) {
        activeScene_->onUnload();
    }
    activeScene_ = scene;
    activeScene_->onLoad();
    return true;
}

bool SceneManager::unloadScene(const std::string& name) {
    auto it = std::find_if(scenes_.begin(), scenes_.end(),
        [&name](const std::unique_ptr<Scene>& s) { return s->getName() == name; });
    
    if (it != scenes_.end()) {
        if (activeScene_ == it->get()) {
            activeScene_->onUnload();
            activeScene_ = nullptr;
        }
        scenes_.erase(it);
        return true;
    }
    return false;
}

Scene* SceneManager::getScene(const std::string& name) {
    for (auto& scene : scenes_) {
        if (scene->getName() == name) {
            return scene.get();
        }
    }
    return nullptr;
}

void SceneManager::update(float deltaTime) {
    if (activeScene_) {
        activeScene_->update(deltaTime);
    }
}

} // namespace lumin
