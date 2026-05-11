#pragma once

#include "entity.h"
#include <unordered_map>
#include <vector>
#include <memory>

namespace lumin {

/**
 * Component Manager - manages components across all entities
 * Allows efficient queries and updates of components by type
 */
class ComponentManager {
public:
    ComponentManager();
    ~ComponentManager();

    // Register a component type
    template<typename T>
    void registerComponentType();

    // Get all components of a type
    template<typename T>
    std::vector<T*> getComponentsOfType();

    // Update all components
    void updateAll(float deltaTime);

private:
    std::unordered_map<size_t, std::vector<std::shared_ptr<Component>>> componentRegistry_;
};

template<typename T>
void ComponentManager::registerComponentType() {
    size_t hash = typeid(T).hash_code();
    if (componentRegistry_.find(hash) == componentRegistry_.end()) {
        componentRegistry_[hash] = std::vector<std::shared_ptr<Component>>();
    }
}

template<typename T>
std::vector<T*> ComponentManager::getComponentsOfType() {
    std::vector<T*> result;
    size_t hash = typeid(T).hash_code();
    auto it = componentRegistry_.find(hash);
    if (it != componentRegistry_.end()) {
        for (auto& comp : it->second) {
            result.push_back(static_cast<T*>(comp.get()));
        }
    }
    return result;
}

} // namespace lumin
