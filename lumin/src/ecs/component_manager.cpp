#include "ecs/component_manager.h"

namespace lumin {

ComponentManager::ComponentManager() {
}

ComponentManager::~ComponentManager() {
    componentRegistry_.clear();
}

void ComponentManager::updateAll(float deltaTime) {
    for (auto& pair : componentRegistry_) {
        for (auto& comp : pair.second) {
            comp->update(deltaTime);
        }
    }
}

} // namespace lumin
