#pragma once

#include "entity.h"
#include <unordered_map>
#include <memory>
#include <vector>

namespace lumin {

/**
 * Entity Manager - manages all entities in the scene
 * Responsible for entity lifecycle management
 */
class EntityManager {
public:
    EntityManager();
    ~EntityManager();

    // Entity creation and destruction
    Entity* createEntity();
    bool destroyEntity(EntityID id);
    
    // Entity retrieval
    Entity* getEntity(EntityID id);
    const std::vector<Entity*>& getEntities() const;
    
    // Query
    size_t getEntityCount() const { return entities_.size(); }
    
    // Update all entities
    void update(float deltaTime);
    
    // Clear all entities
    void clear();

private:
    std::unordered_map<EntityID, std::unique_ptr<Entity>> entityMap_;
    std::vector<Entity*> entities_;
    EntityID nextEntityID_;
};

} // namespace lumin
