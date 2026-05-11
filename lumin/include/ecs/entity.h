#pragma once

#include <cstdint>
#include <vector>
#include <memory>
#include <typeinfo>
#include <unordered_map>

namespace lumin {

// Entity ID type
using EntityID = std::uint32_t;
const EntityID INVALID_ENTITY = 0;

/**
 * Component base class
 * All game components should inherit from this
 */
class Component {
public:
    virtual ~Component() = default;
    virtual void onAttach() {}
    virtual void onDetach() {}
    virtual void update(float deltaTime) {}
};

/**
 * Entity class - represents a game object
 * Holds components and transform information
 */
class Entity {
public:
    explicit Entity(EntityID id);
    ~Entity();

    EntityID getID() const { return id_; }
    bool isActive() const { return active_; }
    void setActive(bool active) { active_ = active; }

    // Component management
    template<typename T, typename... Args>
    T* addComponent(Args&&... args);
    
    template<typename T>
    T* getComponent();
    
    template<typename T>
    bool hasComponent() const;
    
    template<typename T>
    bool removeComponent();

    // Get all components
    const std::vector<std::shared_ptr<Component>>& getComponents() const {
        return components_;
    }

private:
    EntityID id_;
    bool active_;
    std::vector<std::shared_ptr<Component>> components_;
    std::unordered_map<size_t, std::shared_ptr<Component>> componentMap_;
};

// Template implementations
template<typename T, typename... Args>
T* Entity::addComponent(Args&&... args) {
    auto component = std::make_shared<T>(std::forward<Args>(args)...);
    components_.push_back(component);
    componentMap_[typeid(T).hash_code()] = component;
    component->onAttach();
    return component.get();
}

template<typename T>
T* Entity::getComponent() {
    size_t hash = typeid(T).hash_code();
    auto it = componentMap_.find(hash);
    if (it != componentMap_.end()) {
        return static_cast<T*>(it->second.get());
    }
    return nullptr;
}

template<typename T>
bool Entity::hasComponent() const {
    return componentMap_.find(typeid(T).hash_code()) != componentMap_.end();
}

template<typename T>
bool Entity::removeComponent() {
    size_t hash = typeid(T).hash_code();
    auto it = componentMap_.find(hash);
    if (it != componentMap_.end()) {
        it->second->onDetach();
        componentMap_.erase(it);
        // Also remove from vector
        auto& comp = it->second;
        components_.erase(std::remove(components_.begin(), components_.end(), comp), 
                         components_.end());
        return true;
    }
    return false;
}

} // namespace lumin
