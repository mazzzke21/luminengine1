#include "ecs/entity_manager.h"

namespace lumin {

EntityManager::EntityManager()
    : nextEntityID_(1) {
}

EntityManager::~EntityManager() {
    clear();
}

Entity* EntityManager::createEntity() {
    EntityID id = nextEntityID_++;
    auto entity = std::make_unique<Entity>(id);
    Entity* ptr = entity.get();
    entityMap_[id] = std::move(entity);
    entities_.push_back(ptr);
    return ptr;
}

bool EntityManager::destroyEntity(EntityID id) {
    auto it = entityMap_.find(id);
    if (it != entityMap_.end()) {
        Entity* entity = it->second.get();
        entities_.erase(std::remove(entities_.begin(), entities_.end(), entity), entities_.end());
        entityMap_.erase(it);
        return true;
    }
    return false;
}

Entity* EntityManager::getEntity(EntityID id) {
    auto it = entityMap_.find(id);
    if (it != entityMap_.end()) {
        return it->second.get();
    }
    return nullptr;
}

const std::vector<Entity*>& EntityManager::getEntities() const {
    return entities_;
}

void EntityManager::update(float deltaTime) {
    for (auto entity : entities_) {
        if (entity->isActive()) {
            for (const auto& comp : entity->getComponents()) {
                comp->update(deltaTime);
            }
        }
    }
}

void EntityManager::clear() {
    entities_.clear();
    entityMap_.clear();
}

} // namespace lumin
