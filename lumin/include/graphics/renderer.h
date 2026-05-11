#pragma once

#include <memory>

namespace lumin {

class Mesh;
class Material;

/**
 * Renderer - manages rendering system and rendering pipeline
 */
class Renderer {
public:
    Renderer();
    ~Renderer();

    bool initialize(int width, int height, const char* title);
    void shutdown();

    void beginFrame();
    void endFrame();

    void setViewport(int x, int y, int width, int height);
    void setClearColor(float r, float g, float b, float a);
    void clear();

    void renderMesh(const Mesh* mesh, const Material* material);

    // Get window dimensions
    int getWidth() const { return width_; }
    int getHeight() const { return height_; }

    bool shouldClose() const;

private:
    int width_;
    int height_;
    void* window_;  // GLFWwindow*
};

} // namespace lumin
