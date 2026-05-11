#include "ecs/entity.h"

namespace lumin {

Entity::Entity(EntityID id)
    : id_(id), active_(true) {
}

Entity::~Entity() {
    for (auto& comp : components_) {
        comp->onDetach();
    }
    components_.clear();
    componentMap_.clear();
}

} // namespace lumin
