#pragma once

#include <memory>
#include <string>

namespace lumin {

/**
 * Resource Manager - handles loading and caching of game resources
 * Supports meshes, textures, shaders, audio, etc.
 */
class ResourceManager {
public:
    static ResourceManager& getInstance() {
        static ResourceManager instance;
        return instance;
    }

    // Resource loading and caching
    template<typename T>
    std::shared_ptr<T> load(const std::string& name, const std::string& path);

    template<typename T>
    std::shared_ptr<T> get(const std::string& name);

    void unload(const std::string& name);
    void unloadAll();

private:
    ResourceManager() = default;
    std::unordered_map<std::string, std::shared_ptr<void>> resources_;
};

} // namespace lumin
