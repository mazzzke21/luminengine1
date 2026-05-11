# Lumin Game Engine

A modular, professional-grade 3D game engine written in C++ with an Entity Component System (ECS) architecture.

## Features

### Core Systems
- **Entity Component System (ECS)** - Flexible entity and component management
- **3D Graphics Rendering** - OpenGL-based rendering pipeline
- **Physics Simulation** - Bullet Physics integration for realistic physics
- **Audio System** - OpenAL-based audio playback
- **Input Management** - Keyboard, mouse, and gamepad input handling
- **Scene Management** - Multi-scene support with scene transitions
- **Transform Hierarchy** - Parent-child relationships for entities

### Components
- **Transform** - Position, rotation, and scale management
- **MeshRenderer** - Renders 3D geometry
- **Camera** - Defines view into the scene
- **Light** - Illuminates the scene (Directional, Point, Spot)
- **RigidBody** - Physics simulation and forces
- **Collider** - Collision detection (Box, Sphere, Capsule, Mesh)
- **AudioSource** - Sound effect and music playback

### Geometry
- Cube, Sphere, and Plane primitive meshes
- Custom mesh support via vertex/index buffers

## Architecture

```
Lumin Engine
├── Core
│   ├── Transform (hierarchical transforms)
│   ├── Event System (publish/subscribe)
│   └── Resource Manager (asset caching)
├── ECS
│   ├── Entity (game objects)
│   ├── Component (behaviors)
│   └── EntityManager (lifecycle)
├── Graphics
│   ├── Renderer (rendering pipeline)
│   ├── Shader (GLSL shaders)
│   ├── Mesh (geometry data)
│   ├── Texture (image data)
│   └── Material (visual properties)
├── Physics
│   ├── PhysicsEngine (simulation)
│   ├── RigidBody (physics objects)
│   └── Collider (collision shapes)
├── Audio
│   ├── AudioEngine (playback)
│   └── AudioSource (sound objects)
├── Input
│   └── InputManager (user input)
└── Scene
    ├── Scene (game levels)
    └── SceneManager (level management)
```

## Building

### Requirements
- C++17 or later
- CMake 3.20+
- Dependencies (to be installed):
  - GLFW 3 (windowing)
  - GLEW (OpenGL extensions)
  - GLM (math library)
  - Bullet Physics
  - OpenAL (audio)
  - SDL2_mixer (alternative audio)

### Build Steps

```bash
cd lumin
mkdir build
cd build
cmake ..
cmake --build .
```

## Usage Example

```cpp
#include "engine.h"

int main() {
    lumin::Engine engine;
    
    // Initialize with window size and title
    if (!engine.initialize(1280, 720, "My Game")) {
        return 1;
    }

    // Create a scene
    auto scene = engine.getSceneManager().createScene("MainScene");
    engine.getSceneManager().loadScene("MainScene");

    // Create a game entity
    auto entity = scene->createEntity();
    auto transform = entity->addComponent<lumin::Transform>();
    transform->setPosition(glm::vec3(0, 0, 0));
    
    // Add physics
    auto rigidBody = entity->addComponent<lumin::RigidBody>();
    auto collider = entity->addComponent<lumin::Collider>();

    // Run the game loop
    engine.run();

    return 0;
}
```

## Project Structure

```
lumin/
├── CMakeLists.txt          # Build configuration
├── include/
│   ├── engine.h            # Main engine class
│   ├── core/               # Core systems
│   ├── ecs/                # Entity component system
│   ├── graphics/           # Rendering system
│   ├── physics/            # Physics system
│   ├── audio/              # Audio system
│   ├── input/              # Input system
│   └── scene/              # Scene system
├── src/
│   ├── engine.cpp
│   ├── ecs/
│   ├── graphics/
│   ├── physics/
│   ├── audio/
│   ├── input/
│   └── scene/
├── examples/
│   └── main.cpp            # Example game
└── assets/                 # Game assets (models, textures, audio)
```

## Next Steps

1. **Install Dependencies** - Set up GLFW, GLEW, Bullet Physics, OpenAL, and GLM
2. **Implement Graphics** - Complete OpenGL rendering pipeline
3. **Implement Physics** - Integrate Bullet Physics fully
4. **Implement Audio** - Integrate OpenAL audio playback
5. **Add Tools** - Create editor and asset pipeline
6. **Optimize** - Profile and optimize hot paths

## License

This engine is provided as-is for educational and commercial use.

## Author

Lumin Engine - Professional Game Engine Framework
