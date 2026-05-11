#pragma once

#include <glm/glm.hpp>
#include <functional>
#include <unordered_map>
#include <vector>
#include <string>

namespace lumin {

/**
 * Event system for game events
 */
class EventSystem {
public:
    using EventCallback = std::function<void(const std::string&, void*)>;

    static EventSystem& getInstance() {
        static EventSystem instance;
        return instance;
    }

    void subscribe(const std::string& eventName, EventCallback callback) {
        listeners_[eventName].push_back(callback);
    }

    void emit(const std::string& eventName, void* data = nullptr) {
        auto it = listeners_.find(eventName);
        if (it != listeners_.end()) {
            for (const auto& callback : it->second) {
                callback(eventName, data);
            }
        }
    }

private:
    EventSystem() = default;
    std::unordered_map<std::string, std::vector<EventCallback>> listeners_;
};

} // namespace lumin
